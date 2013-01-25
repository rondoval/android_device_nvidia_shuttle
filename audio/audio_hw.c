/*
 * Copyright (C) 2011 The Android Open Source Project
 * Copyright (C) 2011-12 Eduardo Jos� Tagle <ejtagle@tutopia.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "audio_hw_primary"
//#define LOG_NDEBUG 1

#include <errno.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>

#include <cutils/log.h>
#include <cutils/properties.h>
#include <cutils/str_parms.h>

#include <hardware/audio.h>
#include <hardware/hardware.h>

#include <system/audio.h>

#include <tinyalsa/asoundlib.h>


/* Mixer control names */
#define MIXER_PCM_PLAYBACK_VOLUME     		"PCM Playback Volume"
#define MIXER_HEADSET_PLAYBACK_VOLUME       "Headphone Playback Volume"
#define MIXER_SPEAKER_PLAYBACK_VOLUME       "Speaker Playback Volume"
#define MIXER_MIC_CAPTURE_VOLUME            "Mic 2 Capture Volume"

#define MIXER_HEADSET_PLAYBACK_SWITCH       "Headphone Playback Switch"
#define MIXER_SPEAKER_PLAYBACK_SWITCH       "Speaker Playback Switch"
#define MIXER_MIC_LEFT_CAPTURE_SWITCH       "Left Record Mixer Mic2L Capture Switch"
#define MIXER_MIC_RIGHT_CAPTURE_SWITCH      "Right Record Mixer Mic2R Capture Switch"

#define HEADPHONE_JACK_SWITCH				"Headphone Jack Switch"
#define INTERNAL_SPEAKER_SWITCH				"Internal Speaker Switch"
#define INTERNAL_MIC_SWITCH					"Internal Mic Switch"

/* ALSA card */
#define PCM_CARD_SHUTTLE 0

/* ALSA ports for card0 */
#define PCM_DEVICE_MM		0 /* CODEC port */
#define PCM_DEVICE_SCO 		1 /* Bluetooth/3G port */
#define PCM_DEVICE_SPDIF 	2 /* SPDIF (HDMI) port */

/* conversions from Percent to codec gains */
#define PERC_TO_PCM_VOLUME(x)     ( (int)((x) * 31 )) 
#define PERC_TO_CAPTURE_VOLUME(x) ( (int)((x) * 31 ))
#define PERC_TO_HEADSET_VOLUME(x) ( (int)((x) * 31 )) 
#define PERC_TO_SPEAKER_VOLUME(x) ( (int)((x) * 31 )) 

#define OUT_PERIOD_SIZE 880
#define OUT_SHORT_PERIOD_COUNT 2
#define OUT_LONG_PERIOD_COUNT 8
#define OUT_SAMPLING_RATE 44100

#define IN_PERIOD_SIZE 1024
#define IN_PERIOD_COUNT 2
#define IN_SAMPLING_RATE 44100

#define SCO_PERIOD_SIZE 128
#define SCO_PERIOD_COUNT 2
#define SCO_SAMPLING_RATE 8000

#define AUDIO_DEVICE(x) ((x) & (~(AUDIO_DEVICE_BIT_IN | AUDIO_DEVICE_BIT_DEFAULT))) 

/* We need this stabilization time before outputting captured audio to app */
#define FRAMES_MUTED_AT_CAPTURE_START 2048

static const struct pcm_config pcm_config_out = {
    .channels = 2,
    .rate = OUT_SAMPLING_RATE,
    .period_size = OUT_PERIOD_SIZE,
    .period_count = OUT_LONG_PERIOD_COUNT,
    .format = PCM_FORMAT_S16_LE,
    .start_threshold = OUT_PERIOD_SIZE * OUT_SHORT_PERIOD_COUNT,
};

static const struct pcm_config pcm_config_in = {
    .channels = 2,
    .rate = IN_SAMPLING_RATE,
    .period_size = IN_PERIOD_SIZE,
    .period_count = IN_PERIOD_COUNT,
    .format = PCM_FORMAT_S16_LE,
    .start_threshold = 1,
    .stop_threshold = (IN_PERIOD_SIZE * IN_PERIOD_COUNT),
};

static const struct pcm_config pcm_config_sco = {
    .channels = 1,
    .rate = SCO_SAMPLING_RATE,
    .period_size = SCO_PERIOD_SIZE,
    .period_count = SCO_PERIOD_COUNT,
    .format = PCM_FORMAT_S16_LE,
};

struct route_setting
{
    char *ctl_name;
    int intval;
    char *strval;
	short post_delay_ms;	/* Post delay in ms */
};

/* These are values that never change */
struct route_setting defaults[] = {
    /* general */
	{
        .ctl_name = MIXER_SPEAKER_PLAYBACK_VOLUME,
        .intval = PERC_TO_SPEAKER_VOLUME(1.0),
	},
	{
        .ctl_name = MIXER_SPEAKER_PLAYBACK_SWITCH,
        .intval = 1,
	},
    {
        .ctl_name = MIXER_HEADSET_PLAYBACK_VOLUME,
        .intval = PERC_TO_HEADSET_VOLUME(1.0),
    },
    {
        .ctl_name = MIXER_HEADSET_PLAYBACK_SWITCH,
        .intval = 0,
    },
    {
        .ctl_name = "Mono Playback Volume",
        .intval = 0,
    },
    {
        .ctl_name = "Mono Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "PhoneIn Playback Volume",
        .intval = 0,
    },
    {
        .ctl_name = MIXER_PCM_PLAYBACK_VOLUME,
        .intval = PERC_TO_PCM_VOLUME(1.0),
    },
    {
        .ctl_name = "PCM Playback Switch",
        .intval = 1,
    },
    {
        .ctl_name = "LineIn Capture Volume",
        .intval = 0,
    },
    {
        .ctl_name = "Mic 1 Capture Volume",
        .intval = 31,
    },
    {
        .ctl_name = MIXER_MIC_CAPTURE_VOLUME,
        .intval = PERC_TO_CAPTURE_VOLUME(1.0),
    },
    {
        .ctl_name = "Mic 1 Boost Volume",
        .intval = 2,
    },
    {
        .ctl_name = "Mic 2 Boost Volume",
        .intval = 2,
    },
    {
        .ctl_name = "Speaker Amp Type",
        .strval = "Class AB",
    },
    {
        .ctl_name = "Rec Capture Volume",
        .intval = 11,
    },
    {
        .ctl_name = "EQ Mode",
        .strval = "normal",
    },
    {
        .ctl_name = "Right Record Mixer Mic1R Capture Switch",
        .intval = 0,
    },
    {
        .ctl_name = MIXER_MIC_RIGHT_CAPTURE_SWITCH,
        .intval = 1,
    },
    {
        .ctl_name = "Right Record Mixer LineInR Capture Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Right Record Mixer PhoneR Capture Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Right Record Mixer HPMixerR Capture Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Right Record Mixer SPKMixerR Capture Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Right Record Mixer MonoMixerR Capture Switc",
        .intval = 0,
    },
    {
        .ctl_name = "Left Record Mixer Mic1L Capture Switch",
        .intval = 0,
    },
    {
        .ctl_name = MIXER_MIC_LEFT_CAPTURE_SWITCH,
        .intval = 1,
    },
    {
        .ctl_name = "Left Record Mixer LineInL Capture Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Left Record Mixer PhoneL Capture Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Left Record Mixer HPMixerL Capture Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Left Record Mixer SPKMixerL Capture Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Left Record Mixer MonoMixerL Capture Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Speaker Mixer LI2SPK Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Speaker Mixer PHO2SPK Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Speaker Mixer MIC12SPK Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Speaker Mixer MIC22SPK Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Speaker Mixer DAC2SPK Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Mono Mixer LI2MONO Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Mono Mixer MIC12MONO Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Mono Mixer MIC22MONO Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Mono Mixer DAC2MONO Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Mono Mixer ADC2MONO_L Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Mono Mixer ADC2MONO_R Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Right HP Mixer LI2HPR Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Right HP Mixer PHO2HPR Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Right HP Mixer MIC12HPR Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Right HP Mixer MIC22HPR Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Right HP Mixer DAC2HPR Playback Switch",
        .intval = 1,
    },
    {
        .ctl_name = "Right HP Mixer ADCR2HPR Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Left HP Mixer LI2HPL Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Left HP Mixer PHO2HPL Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Left HP Mixer MIC12HPL Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Left HP Mixer MIC22HPL Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Left HP Mixer DAC2HPL Playback Switch",
        .intval = 1,
    },
    {
        .ctl_name = "Left HP Mixer ADCL2HPL Playback Switch",
        .intval = 0,
    },
    {
        .ctl_name = "Right Headphone Out Mux",
        .strval = "HPR Mixer",
    },                  
    {
        .ctl_name = "Left Headphone Out Mux",
        .strval = "HPL Mixer",
    },                                     
    {
        .ctl_name = "Right Speaker Out Mux",
        .strval = "HPR Mixer",
    },                  
    {
        .ctl_name = "Left Speaker Out Mux",
        .strval = "HPL Mixer",
    },                                     
    {
        .ctl_name = "Mono Out Mux",
        .strval = "VMID",
    },                                   
    {
        .ctl_name = INTERNAL_SPEAKER_SWITCH,
        .intval = 1,
    },                           
    {
        .ctl_name = HEADPHONE_JACK_SWITCH,
        .intval = 0,
    },                           
    {
        .ctl_name = INTERNAL_MIC_SWITCH,
        .intval = 1,
    },
    {
        .ctl_name = NULL,
    }
};

/* Headphone playback route */
struct route_setting headphone_route[] = {
	{
        .ctl_name = HEADPHONE_JACK_SWITCH,
		.intval = 1,
	},
	{
		.ctl_name = MIXER_HEADSET_PLAYBACK_SWITCH,
		.intval = 1,
    },
    {
        .ctl_name = INTERNAL_SPEAKER_SWITCH,
		.intval = 0,
    },
    {
        .ctl_name = MIXER_SPEAKER_PLAYBACK_SWITCH,
		.intval = 0,
    },
    {
        .ctl_name = NULL,
    }
};

/* Speaker playback route */
struct route_setting speaker_route[] = {
	{
        .ctl_name = HEADPHONE_JACK_SWITCH,
		.intval = 0,
	},
	{
		.ctl_name = MIXER_HEADSET_PLAYBACK_SWITCH,
		.intval = 0,
	},
    {
        .ctl_name = INTERNAL_SPEAKER_SWITCH,
		.intval = 1,
    },
	{
        .ctl_name = MIXER_SPEAKER_PLAYBACK_SWITCH,
		.intval = 1,
    },
    {
        .ctl_name = NULL,
    }
};

/* Speaker Headphone playback route */
struct route_setting speaker_headphone_route[] = {
	{
        .ctl_name = HEADPHONE_JACK_SWITCH,
		.intval = 1,
	},
	{
		.ctl_name = MIXER_HEADSET_PLAYBACK_SWITCH,
		.intval = 1,
    },
    {
        .ctl_name = INTERNAL_SPEAKER_SWITCH,
		.intval = 1,
    },
    {
        .ctl_name = MIXER_SPEAKER_PLAYBACK_SWITCH,
		.intval = 1,
    },
    {
        .ctl_name = NULL,
    }
};

/* No out route */
struct route_setting no_out_route[] = {
    {
        .ctl_name = HEADPHONE_JACK_SWITCH,
		.intval = 0,
    },
    {
        .ctl_name = MIXER_HEADSET_PLAYBACK_SWITCH,
		.intval = 0,
    },
    {
        .ctl_name = INTERNAL_SPEAKER_SWITCH,
		.intval = 0,
    },
    {
        .ctl_name = MIXER_SPEAKER_PLAYBACK_SWITCH,
		.intval = 0,
    },
    {
        .ctl_name = NULL,
    }
};

struct mixer_ctls
{
	struct mixer_ctl *pcm_volume;
    struct mixer_ctl *headset_volume;
    struct mixer_ctl *speaker_volume;
	struct mixer_ctl *mic_volume;
	struct mixer_ctl *mic_switch_left;
	struct mixer_ctl *mic_switch_right;
};

static int msleep(unsigned long milisec)
{
    struct timespec req;
    
    time_t sec=(int)(milisec/1000);
    milisec = milisec - (sec*1000);
	
	memset(&req,0,sizeof(req));
    req.tv_sec = sec;
    req.tv_nsec = milisec*1000000L;
	
	while(nanosleep(&req,&req)==-1 && errno == EINTR)
         continue;
    return 1;
}

/* The enable flag when 0 makes the assumption that enums are disabled by
 * "Off" and integers/booleans by 0 */
static int set_route_by_array(struct mixer *mixer, struct route_setting *route,
                              int enable)
{
    struct mixer_ctl *ctl;
    unsigned int i, j;

    /* Go through the route array and set each value */
    i = 0;
    while (route[i].ctl_name) {
        ctl = mixer_get_ctl_by_name(mixer, route[i].ctl_name);
        if (!ctl)
            return -EINVAL;

        if (route[i].strval) {
            if (enable)
                mixer_ctl_set_enum_by_string(ctl, route[i].strval);
            else
                mixer_ctl_set_enum_by_string(ctl, "Off");
        } else {
            /* This ensures multiple (i.e. stereo) values are set jointly */
            for (j = 0; j < mixer_ctl_get_num_values(ctl); j++) {
                if (enable)
                    mixer_ctl_set_value(ctl, j, route[i].intval);
                else
                    mixer_ctl_set_value(ctl, j, 0);
            }
        }
		/* Perform a delay if needed for stabilization purposes */
		if (route[i].post_delay_ms) {
			msleep(route[i].post_delay_ms);
		}
        i++;
    }

    return 0;
}

struct audio_device {
    struct audio_hw_device hw_device;

    pthread_mutex_t lock;       /* see note below on mutex acquisition order */
    struct mixer *mixer;
    struct mixer_ctls mixer_ctls;

    bool mic_mute;

    struct stream_out *active_out;		/* Active stream out */
    struct stream_in *active_in;		/* Active stream in */
};

struct stream_out {
    struct audio_stream_out stream;

    pthread_mutex_t lock;       	/* see note below on mutex acquisition order */
    struct pcm *pcm;
    struct pcm_config config;			/* HW config being used */
    bool standby;
	audio_devices_t device;				/* current device */
	struct audio_device *dev;

    int write_threshold;
    int cur_write_threshold;
};

struct stream_in {
    struct audio_stream_in stream;

    pthread_mutex_t lock;       	/* see note below on mutex acquisition order */
    struct pcm *pcm;
    struct pcm_config config;			/* HW config being used */
    bool standby;
	audio_devices_t device;				/* current device */
	struct audio_device *dev;

    unsigned int subsample_shift;	/* Subsampling factor (1<<shift), to emulate different submultiples of sampling rate .Only supported values are 0,1,2 */
	int16_t* buffer;				/* Temporary buffer to make subsampling */
	unsigned int frames_to_mute;	/* Count of samples to be muted. Hw needs some stabilization time, otherwise, a POP is captured that fools Voice Recognizer */
};

static uint32_t out_get_sample_rate(const struct audio_stream *stream);
static size_t out_get_buffer_size(const struct audio_stream *stream);
static audio_format_t out_get_format(const struct audio_stream *stream);
static uint32_t in_get_sample_rate(const struct audio_stream *stream);
static size_t in_get_buffer_size(const struct audio_stream *stream);
static audio_format_t in_get_format(const struct audio_stream *stream);

/*
 * NOTE: when multiple mutexes have to be acquired, always take the
 * audio_device mutex first, followed by the stream_in and/or
 * stream_out mutexes.
 */

/* Helper functions */

static void select_devices(struct audio_device *adev)
{
	/* Get the active audio output */
	audio_devices_t device = adev->active_out ? AUDIO_DEVICE(adev->active_out->device) : 0;
	
	/* Switch between speaker and headphone if required */
	switch (device & AUDIO_DEVICE(AUDIO_DEVICE_OUT_SPEAKER | AUDIO_DEVICE_OUT_WIRED_HEADPHONE)) {
		case 0:
			set_route_by_array(adev->mixer, no_out_route, 1);
			break;
		case AUDIO_DEVICE(AUDIO_DEVICE_OUT_SPEAKER):
			set_route_by_array(adev->mixer, speaker_route, 1);
			break;
		case AUDIO_DEVICE(AUDIO_DEVICE_OUT_WIRED_HEADPHONE):
			set_route_by_array(adev->mixer, headphone_route, 1);
			break;
		case AUDIO_DEVICE(AUDIO_DEVICE_OUT_WIRED_HEADPHONE | AUDIO_DEVICE_OUT_SPEAKER):
			set_route_by_array(adev->mixer, speaker_headphone_route, 1);
			break;
	}

	ALOGD("Headphone out:%c, Speaker out:%c, HDMI out:%c, BT out:%c\n",
		(device & AUDIO_DEVICE(AUDIO_DEVICE_OUT_WIRED_HEADPHONE)) ? 'Y' : 'N',
		(device & AUDIO_DEVICE(AUDIO_DEVICE_OUT_SPEAKER)) ? 'Y' : 'N',
		(device & AUDIO_DEVICE(AUDIO_DEVICE_OUT_AUX_DIGITAL)) ? 'Y' : 'N',
		(device & AUDIO_DEVICE(AUDIO_DEVICE_OUT_ALL_SCO)) ? 'Y' : 'N'
		);

}

/* must be called with hw device and output stream mutexes locked */
static void do_out_standby(struct stream_out *out)
{
    struct audio_device *adev = out->dev;
	
    if (!out->standby) {
        pcm_close(out->pcm);
        out->pcm = NULL;
        adev->active_out = NULL;

        out->standby = true;
    }
}

/* must be called with hw device and input stream mutexes locked */
static void do_in_standby(struct stream_in *in)
{
    struct audio_device *adev = in->dev;
	
    if (!in->standby) {
        pcm_close(in->pcm);
        in->pcm = NULL;
		
		if (in->buffer) {
			free(in->buffer);
			in->buffer = NULL;
		}
		
        adev->active_in = NULL;
	
        in->standby = true;
    }
}

/* must be called with hw device and output stream mutexes locked */
static int start_output_stream(struct stream_out *out)
{
    struct audio_device *adev = out->dev;
    unsigned int device;
    int ret;

    if (AUDIO_DEVICE(out->device) & AUDIO_DEVICE(AUDIO_DEVICE_OUT_ALL_SCO)) {
		/* Bluetooth uses a fixed format */
        device = PCM_DEVICE_SCO;
        memcpy(&out->config,&pcm_config_sco,sizeof(out->config));
    } else {
	    if (AUDIO_DEVICE(out->device) & AUDIO_DEVICE(AUDIO_DEVICE_OUT_AUX_DIGITAL)) {
        	device = PCM_DEVICE_SPDIF;
    	} else {
        	device = PCM_DEVICE_MM;
		}
		
		memcpy(&out->config,&pcm_config_out,sizeof(out->config));
		}
			
	ALOGD("start_output_stream: device:%d, rate:%d, channels:%d",device,out->config.rate, out->config.channels);
    out->pcm = pcm_open(PCM_CARD_SHUTTLE, device, PCM_OUT | PCM_NORESTART, &out->config);

    if (out->pcm && !pcm_is_ready(out->pcm)) {
        ALOGE("pcm_open(out) failed: %s", pcm_get_error(out->pcm));
        pcm_close(out->pcm);
        return -ENOMEM;
    }
	
	adev->active_out = out;

	select_devices(adev);
	
    return 0;
}

/* must be called with hw device and input stream mutexes locked */
static int start_input_stream(struct stream_in *in)
{
    struct audio_device *adev = in->dev;
    unsigned int device;
    int ret;

    if (AUDIO_DEVICE(in->device) & AUDIO_DEVICE(AUDIO_DEVICE_IN_ALL_SCO)) {
        device = PCM_DEVICE_SCO;
        memcpy(&in->config,&pcm_config_sco,sizeof(in->config));
    } else {
	    if (AUDIO_DEVICE(in->device) & AUDIO_DEVICE(AUDIO_DEVICE_IN_AUX_DIGITAL)) {
        	device = PCM_DEVICE_SPDIF;
    	} else {
        	device = PCM_DEVICE_MM;
		}
		memcpy(&in->config,&pcm_config_in,sizeof(in->config));
    }

	ALOGD("start_input_stream: device:%d, rate:%d, channels:%d",device,in->config.rate,in->config.channels);
    in->pcm = pcm_open(PCM_CARD_SHUTTLE, device, PCM_IN, &in->config);

    if (in->pcm && !pcm_is_ready(in->pcm)) {
        ALOGE("pcm_open(in) failed: %s", pcm_get_error(in->pcm));
        pcm_close(in->pcm);
        return -ENOMEM;
    }

	/* If needed, allocate the resample buffer */
	if (in->subsample_shift) {
		in->buffer = malloc(in->config.period_size * in->config.channels * sizeof(int16_t));
	}
	
	/* Mute some samples at start of capture, to let line calm down */
	in->frames_to_mute = FRAMES_MUTED_AT_CAPTURE_START;
	
	adev->active_in = in;
	
	select_devices(adev);
	
    return 0;
}

/* xface */
static uint32_t out_get_sample_rate(const struct audio_stream *stream)
{
	ALOGD("out_get_sample_rate");
    return ((struct stream_out*)stream)->config.rate;
}

/* xface */
static int out_set_sample_rate(struct audio_stream *stream, uint32_t rate)
{
    struct stream_out *out = (struct stream_out *)stream;
	ALOGD("out_set_sample_rate: %d",rate);
	
	if (rate == out->config.rate)
    return 0;
    return -ENOSYS;
}

/* xface */
static size_t out_get_buffer_size(const struct audio_stream *stream)
{
	ALOGD("out_get_buffer_size");
    return ((struct stream_out*)stream)->config.period_size *
               audio_stream_frame_size((struct audio_stream *)stream);
}

/* xface */
static uint32_t out_get_channels(const struct audio_stream *stream)
{
    struct stream_out *out = (struct stream_out *)stream;
	//ALOGV("out_get_channels");
	return ((struct stream_out*)stream)->config.channels == 2 
		? AUDIO_CHANNEL_OUT_STEREO
		: AUDIO_CHANNEL_OUT_MONO;
}

/* xface */
static audio_format_t out_get_format(const struct audio_stream *stream)
{
	//ALOGV("out_get_format");
    return AUDIO_FORMAT_PCM_16_BIT;
}

/* xface */
static int out_set_format(struct audio_stream *stream, audio_format_t format)
{
	ALOGD("out_set_format: %d", format);
	if (format == AUDIO_FORMAT_PCM_16_BIT)
		return 0;
    return -ENOSYS;
}

/* xface */
static int out_standby(struct audio_stream *stream)
{
    struct stream_out *out = (struct stream_out *)stream;

    pthread_mutex_lock(&out->dev->lock);
    pthread_mutex_lock(&out->lock);
    do_out_standby(out);
    pthread_mutex_unlock(&out->lock);
    pthread_mutex_unlock(&out->dev->lock);

    return 0;
}

/* xface */
static int out_dump(const struct audio_stream *stream, int fd)
{
    return 0;
}

/* xface */
static int out_set_parameters(struct audio_stream *stream, const char *kvpairs)
{
    struct stream_out *out = (struct stream_out *)stream;
    struct audio_device *adev = out->dev;
    struct str_parms *parms;
    char value[32];
    int ret;
    unsigned int val;
	
    parms = str_parms_create_str(kvpairs);

    ret = str_parms_get_str(parms, AUDIO_PARAMETER_STREAM_ROUTING,
                            value, sizeof(value));
    pthread_mutex_lock(&adev->lock);
	pthread_mutex_lock(&out->lock);
    if (ret >= 0) {
        val = atoi(value);
        if ((out->device != val) && (val != 0)) {
			ALOGD("out_set_parameters: routing: 0x%08x", val);
            /*
             * If SCO is turned on/off or HDMI is turned on/off,
			 *  we need to put audio into standby
             *  because SCO/HDMI uses a different PCM.
             */
            if ( AUDIO_DEVICE(val ^ out->device) & AUDIO_DEVICE(AUDIO_DEVICE_OUT_ALL_SCO | AUDIO_DEVICE_OUT_AUX_DIGITAL) ) {
                do_out_standby(out);
			}
				
            out->device = val;
            select_devices(adev);
        }
        }
	pthread_mutex_unlock(&out->lock);
        pthread_mutex_unlock(&adev->lock);

    str_parms_destroy(parms);
    return ret;
}

/* xface */
static char * out_get_parameters(const struct audio_stream *stream, const char *keys)
{
    return strdup("");
}

/* xface */
static uint32_t out_get_latency(const struct audio_stream_out *stream)
{
    struct stream_out *out = (struct stream_out *)stream;
    struct audio_device *adev = out->dev;

    return (out->config.period_size * out->config.period_count  * 1000) / 
			out->config.rate;
}

/* xface */
static int out_set_volume(struct audio_stream_out *stream, float left,
                          float right)
{
    struct stream_out *out = (struct stream_out *)stream;
    struct audio_device *adev = out->dev;
	
	ALOGD("out_set_volume: left:%f, right:%f\n",left,right);

	mixer_ctl_set_value(adev->mixer_ctls.speaker_volume, 0,
		PERC_TO_SPEAKER_VOLUME(left));
	mixer_ctl_set_value(adev->mixer_ctls.speaker_volume, 1,
		PERC_TO_SPEAKER_VOLUME(right));
		
	mixer_ctl_set_value(adev->mixer_ctls.headset_volume, 0,
		PERC_TO_HEADSET_VOLUME(left));
	mixer_ctl_set_value(adev->mixer_ctls.headset_volume, 1,
		PERC_TO_HEADSET_VOLUME(right));

    return 0;
}

/* xface */
static ssize_t out_write(struct audio_stream_out *stream, const void* buffer,
                         size_t bytes)
{
    int ret = 0;
    struct stream_out *out = (struct stream_out *)stream;
    struct audio_device *adev = out->dev;
	
    size_t frame_size = audio_stream_frame_size(&out->stream.common);
    int16_t *in_buffer = (int16_t *)buffer;
    size_t in_frames = bytes / frame_size;

	
    /*
     * acquiring hw device mutex systematically is useful if a low
     * priority thread is waiting on the output stream mutex - e.g.
     * executing out_set_parameters() while holding the hw device
     * mutex
     */
    pthread_mutex_lock(&adev->lock);
    pthread_mutex_lock(&out->lock);
    if (out->standby) {
        ret = start_output_stream(out);
        if (ret == 0)
        out->standby = false;
    }
    pthread_mutex_unlock(&adev->lock);
	
    if (ret < 0) {
		ALOGE("out_read: Failed to start output stream");
        goto exit;
	}

    ret = pcm_write(out->pcm, in_buffer, in_frames * frame_size);

exit:
    pthread_mutex_unlock(&out->lock);

    if (ret != 0) {
        usleep(bytes * 1000000 / frame_size /
               out->config.rate);
    }

    return bytes;
}

/* xface */
static int out_get_render_position(const struct audio_stream_out *stream,
                                   uint32_t *dsp_frames)
{
	ALOGD("out_get_render_position");
    return -EINVAL;
}

/* xface */
static int out_add_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
	ALOGD("out_add_audio_effect");
    return 0;
}

/* xface */
static int out_remove_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
	ALOGD("out_remove_audio_effect");
    return 0;
}

/* xface */
static int out_get_next_write_timestamp(const struct audio_stream_out *stream,
                                        int64_t *timestamp)
{
	//ALOGV("out_get_next_write_timestamp");
    return -EINVAL;
}

/** audio_stream_in implementation **/

/* xface */
static uint32_t in_get_sample_rate(const struct audio_stream *stream)
{
    struct stream_in *in = (struct stream_in *)stream;
	//ALOGD("in_get_sample_rate");
    return in->config.rate >> in->subsample_shift;
}

/* xface */
static int in_set_sample_rate(struct audio_stream *stream, uint32_t rate)
{
    struct stream_in *in = (struct stream_in *)stream;
	ALOGD("in_set_sample_rate: %d",rate);
	
	if (rate == (in->config.rate >> in->subsample_shift))
    return 0;
    return -ENOSYS;
}

/* xface */
static size_t in_get_buffer_size(const struct audio_stream *stream)
{
    struct stream_in *in = (struct stream_in *)stream;
    size_t size;

	ALOGD("in_get_buffer_size");
	
    size = in->config.period_size;
    size = ((size + 15) / 16) * 16;

    return size * audio_stream_frame_size((struct audio_stream *)stream);
}

/* xface */
static uint32_t in_get_channels(const struct audio_stream *stream)
{
    struct stream_in *in = (struct stream_in *)stream;
	return ((struct stream_in*)stream)->config.channels == 2 
		? AUDIO_CHANNEL_IN_STEREO
		: AUDIO_CHANNEL_IN_MONO;
}

/* xface */
static audio_format_t in_get_format(const struct audio_stream *stream)
{
	//ALOGD("in_get_format");
    return AUDIO_FORMAT_PCM_16_BIT;
}

/* xface */
static int in_set_format(struct audio_stream *stream, audio_format_t format)
{
	ALOGD("in_set_format: %d",format);
	if (format == AUDIO_FORMAT_PCM_16_BIT)
		return 0;
    return -ENOSYS;
}


/* xface */
static int in_standby(struct audio_stream *stream)
{
    struct stream_in *in = (struct stream_in *)stream;
	ALOGD("in_standby");

    pthread_mutex_lock(&in->dev->lock);
    pthread_mutex_lock(&in->lock);
    do_in_standby(in);
    pthread_mutex_unlock(&in->lock);
    pthread_mutex_unlock(&in->dev->lock);

    return 0;
}

/* xface */
static int in_dump(const struct audio_stream *stream, int fd)
{
	ALOGD("in_dump");
    return 0;
}

/* xface */
static int in_set_parameters(struct audio_stream *stream, const char *kvpairs)
{
    struct stream_in *in = (struct stream_in *)stream;
    struct audio_device *adev = in->dev;
    struct str_parms *parms;
    char value[32];
    int ret;
    unsigned int val;
	ALOGD("in_set_parameters: %s",kvpairs);

    parms = str_parms_create_str(kvpairs);


    ret = str_parms_get_str(parms, AUDIO_PARAMETER_STREAM_ROUTING,
                            value, sizeof(value));
    pthread_mutex_lock(&adev->lock);
    pthread_mutex_lock(&in->lock);
    if (ret >= 0) {
        val = atoi(value);
        if ( (in->device != val) && (val != 0) ) {
			ALOGD("in_set_parameters: routing: 0x%08x", val);
		 
            /*
             * If SCO is turned on/off or HDMI is turned on/off,
			 *  we need to put audio into standby
             * because SCO uses a different PCM.
             */
            if ( AUDIO_DEVICE(val ^ in->device) & AUDIO_DEVICE(AUDIO_DEVICE_IN_ALL_SCO | AUDIO_DEVICE_IN_AUX_DIGITAL) ) {
                do_in_standby(in);
    }

			in->device = val;
            select_devices(adev);
        }
    }
	pthread_mutex_unlock(&in->lock);
    pthread_mutex_unlock(&adev->lock);

    str_parms_destroy(parms);
    return ret;
}

/* xface */
static char * in_get_parameters(const struct audio_stream *stream,
                                const char *keys)
{
	ALOGD("in_get_parameters");
    return strdup("");
}

/* xface */
static int in_set_gain(struct audio_stream_in *stream, float gain)
{
    struct stream_in *in = (struct stream_in *)stream;
    struct audio_device *adev = in->dev;

	unsigned int channel;
	ALOGD("in_set_gain: %f",gain);
	
    for (channel = 0; channel < 2; channel++) {
        mixer_ctl_set_value(adev->mixer_ctls.mic_volume, channel,
            PERC_TO_CAPTURE_VOLUME(gain));
        mixer_ctl_set_value(adev->mixer_ctls.mic_volume, channel,
            PERC_TO_CAPTURE_VOLUME(gain));
    }

    return 0;
}

/* xface */
static ssize_t in_read(struct audio_stream_in *stream, void* buffer,
                       size_t bytes)
{
    int ret = 0;
    struct stream_in *in = (struct stream_in *)stream;
    struct audio_device *adev = in->dev;
	
	int frame_size = audio_stream_frame_size(&stream->common);
    size_t in_frames = bytes / frame_size;
	
	int16_t* in_buffer = (int16_t*)buffer;

	//ALOGD("in_read: bytes:%d",bytes);
	
    /*
     * acquiring hw device mutex systematically is useful if a low
     * priority thread is waiting on the input stream mutex - e.g.
     * executing in_set_parameters() while holding the hw device
     * mutex
     */
    pthread_mutex_lock(&adev->lock);
    pthread_mutex_lock(&in->lock);
    if (in->standby) {
        ret = start_input_stream(in);
        if (ret == 0)
            in->standby = false;
    }
    pthread_mutex_unlock(&adev->lock);

    if (ret < 0) {
		ALOGE("in_read: Failed to start input stream");
        goto exit;
	}

	/* If subsampling, we need to read more samples using the temporary buffer */
	if (in->subsample_shift) {
		int16_t* outp = in_buffer;
	
		/* We must read in chunks ... */
		unsigned int chunkstodo = 1 << in->subsample_shift;
		do {
			unsigned int frames_to_do = in_frames >> in->subsample_shift;
		
			/* Read requested samples, so we can subsample */
			//ALOGD("in_read: subsampling: pcm_read: buf:%p, bufsz:%d",in->buffer, in_frames * frame_size);
			ret = pcm_read(in->pcm, in->buffer, in_frames * frame_size);

		/* We always capture 16bit stereo... Downsample...  */		
			if (ret < 0) 
				break;
			ret = 0;
			
			/* If no frames to subsample, skip subsampling */
			if (frames_to_do <= 0) 
				break;
		
			//ALOGD("subsampling...");
			/*
			* Instead of writing zeroes here, we could trust the hardware
			* to always provide zeroes when muted.
			*/
			if (ret == 0 && 
				(adev->mic_mute || in->frames_to_mute)
			) {
				memset(outp, 0, frames_to_do * 4);
				outp += 2 * frames_to_do;
			} else {
				if (in->subsample_shift == 1) {
					int16_t* inp = in->buffer;
					do {
						int c1 = *inp++;
						int c2 = *inp++;
						c1 += *inp++;
						c2 += *inp++;
						*outp++ = c1 >> 1;
						*outp++ = c2 >> 1;
					} while (--frames_to_do);
				} else {
					/* subsample shift == 2 */
					int16_t* inp = in->buffer;
					do {
						int c1 = *inp++;
						int c2 = *inp++;
						c1 += *inp++;
						c2 += *inp++;
						c1 += *inp++;
						c2 += *inp++;
						c1 += *inp++;
						c2 += *inp++;
						*outp++ = c1 >> 2;
						*outp++ = c2 >> 2;
					} while (--frames_to_do);
			}
		}
			//ALOGD("done...");

		} while (--chunkstodo);
	
	} else {

		ret = pcm_read(in->pcm, in_buffer, in_frames * frame_size);
	    if (ret > 0)
	        ret = 0;
	
	    /*
	     * Instead of writing zeroes here, we could trust the hardware
	     * to always provide zeroes when muted.
	     */
		if (ret == 0 && (adev->mic_mute || in->frames_to_mute))
	        memset(buffer, 0, bytes);

	}

	/* Decrement the number of samples to be muted if any */
	if (in->frames_to_mute) {
		if (in->frames_to_mute < in_frames) {
			in->frames_to_mute = 0;
		} else {
			in->frames_to_mute -= in_frames; 
		}
	}
	
exit:
	pthread_mutex_unlock(&in->lock);
	
    if (ret < 0)
        usleep(bytes * 1000000 / frame_size /
                (in->config.rate >> in->subsample_shift) );

    return bytes;
}

/* xface */
static uint32_t in_get_input_frames_lost(struct audio_stream_in *stream)
{
	ALOGD("in_get_input_frames_lost");
    return 0;
}

/* xface */
static int in_add_audio_effect(const struct audio_stream *stream,
                               effect_handle_t effect)
{
    struct stream_in *in = (struct stream_in *)stream;
	ALOGD("in_add_audio_effect");
	return 0;
}

/* xface */
static int in_remove_audio_effect(const struct audio_stream *stream,
                                  effect_handle_t effect)
{
    struct stream_in *in = (struct stream_in *)stream;
	ALOGD("in_remove_audio_effect");
	return 0;
}

/* xface */
static int adev_open_output_stream(struct audio_hw_device *dev,
                                   audio_io_handle_t handle,
                                   audio_devices_t devices,
                                   audio_output_flags_t flags,
                                   struct audio_config *config,
                                   struct audio_stream_out **stream_out)
{
    struct audio_device *adev = (struct audio_device *)dev;
    struct stream_out *out;
    int ret;

	ALOGD("adev_open_output_stream: device: 0x%08x, channel_count:%d", devices, popcount(config->channel_mask));

    if (AUDIO_DEVICE(devices) == AUDIO_DEVICE(AUDIO_DEVICE_NONE))
        devices = AUDIO_DEVICE_OUT_SPEAKER;

	/* Compute the allowed channel mask and sampling rate for the requested device */
	audio_channel_mask_t allowed_channels = 
		(AUDIO_DEVICE(devices) & AUDIO_DEVICE(AUDIO_DEVICE_OUT_ALL_SCO))   
			? AUDIO_CHANNEL_OUT_MONO
			: AUDIO_CHANNEL_OUT_STEREO;
	uint32_t allowed_sampling_rate = 
		(AUDIO_DEVICE(devices) & AUDIO_DEVICE(AUDIO_DEVICE_OUT_ALL_SCO))
			? SCO_SAMPLING_RATE
			: OUT_SAMPLING_RATE;
	
    out = (struct stream_out *)calloc(1, sizeof(struct stream_out));
    if (!out)
        return -ENOMEM;

    out->stream.common.get_sample_rate = out_get_sample_rate;
    out->stream.common.set_sample_rate = out_set_sample_rate;
    out->stream.common.get_buffer_size = out_get_buffer_size;
    out->stream.common.get_channels = out_get_channels;
    out->stream.common.get_format = out_get_format;
    out->stream.common.set_format = out_set_format;
    out->stream.common.standby = out_standby;
    out->stream.common.dump = out_dump;
    out->stream.common.set_parameters = out_set_parameters;
    out->stream.common.get_parameters = out_get_parameters;
    out->stream.common.add_audio_effect = out_add_audio_effect;
    out->stream.common.remove_audio_effect = out_remove_audio_effect;
    out->stream.get_latency = out_get_latency;
    out->stream.set_volume = out_set_volume;
    out->stream.write = out_write;
    out->stream.get_render_position = out_get_render_position;
    out->stream.get_next_write_timestamp = out_get_next_write_timestamp;

    out->dev = adev;
	out->standby = true;
	out->device = devices;
	
	/* Suggest the playback format to the framework, otherwise it crashes */
	config->format = AUDIO_FORMAT_PCM_16_BIT;
	config->channel_mask = allowed_channels;
	config->sample_rate = allowed_sampling_rate;
	
	memcpy(&out->config,
		(AUDIO_DEVICE(devices) & AUDIO_DEVICE(AUDIO_DEVICE_OUT_ALL_SCO))
			? &pcm_config_sco 
			: &pcm_config_out,
		sizeof(out->config)); /* default PCM config */

    *stream_out = &out->stream;
    return 0;

err_open:
    free(out);
    *stream_out = NULL;
    return ret;
}

/* xface */
static void adev_close_output_stream(struct audio_hw_device *dev,
                                     struct audio_stream_out *stream)
{
	ALOGD("adev_close_output_stream");
    out_standby(&stream->common);
    free(stream);
}

/* xface */
static int adev_set_parameters(struct audio_hw_device *dev, const char *kvpairs)
{
    struct audio_device *adev = (struct audio_device *)dev;
   
	ALOGD("adev_set_parameters: kppairs: %s", kvpairs);
    return 0;
}

/* xface */
static char * adev_get_parameters(const struct audio_hw_device *dev,
                                  const char *keys)
{
    return strdup("");
}

/* xface */
static int adev_init_check(const struct audio_hw_device *dev)
{
    return 0;
}

/* xface */
static int adev_set_voice_volume(struct audio_hw_device *dev, float volume)
{
	ALOGD("adev_set_voice_volume: volume: %f", volume);
	
    return -ENOSYS;
}

/* xface */
static int adev_set_master_volume(struct audio_hw_device *dev, float volume)
{
	struct audio_device *adev = (struct audio_device *)dev;

	ALOGD("adev_set_master_volume: volume: %f", volume);
	
	mixer_ctl_set_value(adev->mixer_ctls.pcm_volume, 0,
		PERC_TO_PCM_VOLUME(volume));
	mixer_ctl_set_value(adev->mixer_ctls.pcm_volume, 1,
		PERC_TO_PCM_VOLUME(volume));

    return 0;
}

/* xface */
static int adev_set_mode(struct audio_hw_device *dev, int mode)
{
	ALOGD("adev_set_mode: mode: %d", mode);
    return 0;
}

/* xface */
static int adev_set_mic_mute(struct audio_hw_device *dev, bool state)
{
    struct audio_device *adev = (struct audio_device *)dev;

	ALOGD("adev_set_mic_mute: state: %d", state);
	
	/* Get device lock */
    pthread_mutex_lock(&adev->lock);	
	
	/* If already capturing ... */	
	if (adev->active_in) {
		pthread_mutex_lock(&adev->active_in->lock);
		/* If unmuting, leave some time with forced silence, so the line stabilizes */
		if (!state && adev->mic_mute) {
		
			/* Mute some samples at start of capture, to let line calm down */
			adev->active_in->frames_to_mute = FRAMES_MUTED_AT_CAPTURE_START;
		}
		pthread_mutex_unlock(&adev->active_in->lock);
	}
	
	/* Store setting */
    adev->mic_mute = state;

	/* Release device lock */
    pthread_mutex_unlock(&adev->lock);

	/* Disable mic if requested */
	mixer_ctl_set_value(adev->mixer_ctls.mic_switch_left, 0,	state ? 0 : 1);
	mixer_ctl_set_value(adev->mixer_ctls.mic_switch_right, 0,	state ? 0 : 1);
	
    return 0;
}

/* xface */
static int adev_get_mic_mute(const struct audio_hw_device *dev, bool *state)
{
    struct audio_device *adev = (struct audio_device *)dev;

    *state = adev->mic_mute;

    return 0;
}

/* xface */
static size_t adev_get_input_buffer_size(const struct audio_hw_device *dev,
                                         const struct audio_config *config)
{
    size_t size;
	ALOGD("adev_get_input_buffer_size: sample_rate: %d, format: %d, channel_count:%d", config->sample_rate, config->format, popcount(config->channel_mask));
	
    size = pcm_config_in.period_size;
    size = ((size + 15) / 16) * 16;

    return size * popcount(config->channel_mask) * audio_bytes_per_sample(config->format);
}

/* xface */
static int adev_open_input_stream(struct audio_hw_device *dev,
                                  audio_io_handle_t handle,
                                  audio_devices_t devices,
                                  struct audio_config *config,
                                  struct audio_stream_in **stream_in)
{
    struct audio_device *adev = (struct audio_device *)dev;
    struct stream_in *in;
    int ret;

	ALOGD("adev_open_input_stream: device: 0x%08x, channel_count:%d", devices, popcount(config->channel_mask));
	
    if (AUDIO_DEVICE(devices) == AUDIO_DEVICE(AUDIO_DEVICE_NONE))
        devices = AUDIO_DEVICE_IN_BUILTIN_MIC;
		
	/* Compute the allowed channel mask and sampling rate for the requested device */
	audio_channel_mask_t allowed_channels = 
		(AUDIO_DEVICE(devices) & AUDIO_DEVICE(AUDIO_DEVICE_IN_ALL_SCO))
			? AUDIO_CHANNEL_IN_MONO
			: AUDIO_CHANNEL_IN_STEREO;
	uint32_t allowed_sampling_rate = 
		(AUDIO_DEVICE(devices) & AUDIO_DEVICE(AUDIO_DEVICE_IN_ALL_SCO))
			? SCO_SAMPLING_RATE
			: IN_SAMPLING_RATE;
	
	/* Check if we support the requested format ... Also accept decimation of sampling frequencies in powers of 2 - We will downsample in sw*/
	if (config->format != AUDIO_FORMAT_PCM_16_BIT ||
		config->channel_mask != allowed_channels ||
		( config->sample_rate !=  allowed_sampling_rate && 
		  config->sample_rate != (allowed_sampling_rate>>1) &&
		  config->sample_rate != (allowed_sampling_rate>>2) )
		) {
		ALOGD("adev_open_input_stream: Unsupported format. Let AudioFlinger do the conversion by returning the acceptable format");

		/* Suggest the record format to the framework, otherwise it crashes */
		config->format = AUDIO_FORMAT_PCM_16_BIT;
		config->channel_mask = allowed_channels;

		/* But there is a catch here... AudioFlinger can't downsample to less than half
		   the sampling rate... So we have to handle it somehow - We have implemented a
		   decimation by power of 2 filter ... Select the proper reported sampling frequency */
		if (config->sample_rate >= (allowed_sampling_rate>>1) ) {
			config->sample_rate = allowed_sampling_rate;	
		} else if (config->sample_rate >= (allowed_sampling_rate>>2) ) {
			config->sample_rate = (allowed_sampling_rate>>1);
		} else {
			config->sample_rate = (allowed_sampling_rate>>2);
		}
		
		/* Let audioflinger adopt our suggested rate */
		return -EINVAL;
	}

	ALOGD("adev_open_input_stream: format accepted");
	
	*stream_in = NULL;

    in = (struct stream_in *)calloc(1, sizeof(struct stream_in));
    if (!in)
        return -ENOMEM;

    in->stream.common.get_sample_rate = in_get_sample_rate;
    in->stream.common.set_sample_rate = in_set_sample_rate;
    in->stream.common.get_buffer_size = in_get_buffer_size;
    in->stream.common.get_channels = in_get_channels;
    in->stream.common.get_format = in_get_format;
    in->stream.common.set_format = in_set_format;
    in->stream.common.standby = in_standby;
    in->stream.common.dump = in_dump;
    in->stream.common.set_parameters = in_set_parameters;
    in->stream.common.get_parameters = in_get_parameters;
    in->stream.common.add_audio_effect = in_add_audio_effect;
    in->stream.common.remove_audio_effect = in_remove_audio_effect;
    in->stream.set_gain = in_set_gain;
    in->stream.read = in_read;
    in->stream.get_input_frames_lost = in_get_input_frames_lost;

    in->dev = adev;
    in->standby = true;
	in->device = devices;
	
	memcpy(&in->config,
		(AUDIO_DEVICE(devices) & AUDIO_DEVICE(AUDIO_DEVICE_IN_ALL_SCO))
			? &pcm_config_sco 
			: &pcm_config_in,
		sizeof(in->config)); /* default PCM config */
	
	/* Calculate the audio subsampling factor */
	if (config->sample_rate == allowed_sampling_rate) {
		in->subsample_shift = 0;
	} else if (config->sample_rate == (allowed_sampling_rate>>1)) {
		in->subsample_shift = 1;
	} else {
		in->subsample_shift = 2;
	}
	ALOGD("adev_open_input_stream: Using subsampling shift: %d",in->subsample_shift);

    *stream_in = &in->stream;
    return 0;
}

/* xface */
static void adev_close_input_stream(struct audio_hw_device *dev,
                                   struct audio_stream_in *stream)
{
    struct stream_in *in = (struct stream_in *)stream;

	ALOGD("adev_close_input_stream");
	
    in_standby(&stream->common);
    free(stream);
}

/* xface */
static int adev_dump(const audio_hw_device_t *device, int fd)
{
    return 0;
}

/* xface */
static int adev_close(hw_device_t *device)
{
    struct audio_device *adev = (struct audio_device *)device;
	
	ALOGD("adev_close");

    mixer_close(adev->mixer);
    free(device);
    return 0;
}

static int adev_open(const hw_module_t* module, const char* name,
                     hw_device_t** device)
{
    struct audio_device *adev;
    int ret;

	ALOGE("adev_open: name:'%s'",name);
	
    if (strcmp(name, AUDIO_HARDWARE_INTERFACE) != 0)
        return -EINVAL;

    adev = calloc(1, sizeof(struct audio_device));
    if (!adev)
        return -ENOMEM;

    adev->hw_device.common.tag = HARDWARE_DEVICE_TAG;
    adev->hw_device.common.version = AUDIO_DEVICE_API_VERSION_2_0;
    adev->hw_device.common.module = (struct hw_module_t *) module;
    adev->hw_device.common.close = adev_close;

//    adev->hw_device.get_supported_devices = adev_get_supported_devices;
    adev->hw_device.init_check = adev_init_check;
    adev->hw_device.set_voice_volume = adev_set_voice_volume;
    adev->hw_device.set_master_volume = adev_set_master_volume;
    adev->hw_device.set_mode = adev_set_mode;
    adev->hw_device.set_mic_mute = adev_set_mic_mute;
    adev->hw_device.get_mic_mute = adev_get_mic_mute;
    adev->hw_device.set_parameters = adev_set_parameters;
    adev->hw_device.get_parameters = adev_get_parameters;
    adev->hw_device.get_input_buffer_size = adev_get_input_buffer_size;
    adev->hw_device.open_output_stream = adev_open_output_stream;
    adev->hw_device.close_output_stream = adev_close_output_stream;
    adev->hw_device.open_input_stream = adev_open_input_stream;
    adev->hw_device.close_input_stream = adev_close_input_stream;
    adev->hw_device.dump = adev_dump;

    adev->mixer = mixer_open(0);
    if (!adev->mixer) {
        free(adev);
        ALOGE("Unable to open the mixer, aborting.");
        return -EINVAL;
    }

    adev->mixer_ctls.mic_volume = mixer_get_ctl_by_name(adev->mixer,
                                           MIXER_MIC_CAPTURE_VOLUME);
	if (!adev->mixer_ctls.mic_volume) { 
		ALOGE("Unable to find '%s' mixer control",MIXER_MIC_CAPTURE_VOLUME);
		goto error_out;
	}
	
    adev->mixer_ctls.pcm_volume = mixer_get_ctl_by_name(adev->mixer,
                                           MIXER_PCM_PLAYBACK_VOLUME);
	if (!adev->mixer_ctls.pcm_volume) { 
		ALOGE("Unable to find '%s' mixer control",MIXER_PCM_PLAYBACK_VOLUME);
		goto error_out;
	}
										   
    adev->mixer_ctls.headset_volume = mixer_get_ctl_by_name(adev->mixer,
                                           MIXER_HEADSET_PLAYBACK_VOLUME);
	if (!adev->mixer_ctls.headset_volume) { 
		ALOGE("Unable to find '%s' mixer control",MIXER_HEADSET_PLAYBACK_VOLUME);
		goto error_out;
	}
										   
    adev->mixer_ctls.speaker_volume = mixer_get_ctl_by_name(adev->mixer,
                                           MIXER_SPEAKER_PLAYBACK_VOLUME);
	if (!adev->mixer_ctls.speaker_volume) { 
		ALOGE("Unable to find '%s' mixer control",MIXER_SPEAKER_PLAYBACK_VOLUME);
		goto error_out;
	}

    adev->mixer_ctls.mic_switch_left = mixer_get_ctl_by_name(adev->mixer,
                                           MIXER_MIC_LEFT_CAPTURE_SWITCH);
	if (!adev->mixer_ctls.mic_switch_left) { 
		ALOGE("Unable to find '%s' mixer control",MIXER_MIC_LEFT_CAPTURE_SWITCH);
		goto error_out;
	}

    adev->mixer_ctls.mic_switch_right = mixer_get_ctl_by_name(adev->mixer,
                                           MIXER_MIC_RIGHT_CAPTURE_SWITCH);
	if (!adev->mixer_ctls.mic_switch_right) { 
		ALOGE("Unable to find '%s' mixer control",MIXER_MIC_RIGHT_CAPTURE_SWITCH);
		goto error_out;
	}

	
    /* Set the default route before the PCM stream is opened */
    pthread_mutex_lock(&adev->lock);
    set_route_by_array(adev->mixer, defaults, 1);
    pthread_mutex_unlock(&adev->lock);

    *device = &adev->hw_device.common;

    return 0;

error_out:	

#if !LOG_NDEBUG
	/* To aid debugging, dump all mixer controls */
	{
		unsigned int cnt = mixer_get_num_ctls(adev->mixer);
		unsigned int i;
		ALOGD("Mixer dump: Nr of controls: %d",cnt);
		for (i = 0; i < cnt; i++) {
			struct mixer_ctl* x = mixer_get_ctl(adev->mixer,i);
			if (x != NULL) {
				const char* name;
				const char* type;
				name = mixer_ctl_get_name(x);
				type = mixer_ctl_get_type_string(x);
				ALOGD("#%d: '%s' [%s]",i,name,type);		
			}
		}
	}
#endif

    mixer_close(adev->mixer);
    free(adev);
    return -EINVAL;
	
}

static struct hw_module_methods_t hal_module_methods = {
    .open = adev_open,
};

struct audio_module HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = AUDIO_MODULE_API_VERSION_0_1,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = AUDIO_HARDWARE_MODULE_ID,
        .name = "Shuttle audio HW HAL",
        .author = "The Android Open Source Project",
        .methods = &hal_module_methods,
    },
};
