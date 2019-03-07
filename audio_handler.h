#include "portaudio.h"
#include "Lib/portaudio/src/common/pa_ringbuffer.h"
#include "Lib/portaudio/src/common/pa_util.h"
#include <vector>
#include "Lib/Gist/src/Gist.h"

#define SAMPLE_RATE 48000
#define FRAME_SIZE 512
typedef float SAMPLE;



struct ring_buffer
{
	PaUtilRingBuffer rb_incoming;
	void *rb_incoming_data;
};

struct sound_attributes
{
	float pitch;
	float rms;
	float spectral_centroid;
	float spectral_flatness;
};


class Audio_handler
{
public:
	Audio_handler();
	~Audio_handler();

	void initialize_default();
	void initialize_choose_input();
	sound_attributes update();

private:
	static int callback(const void *input, void *output, unsigned long frameCount,
		const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

	int i_channel_selectors[2]; // Asio requires the channels to be specified
	int o_channel_selectors[2]; // Asio requires the channels to be specified
	ring_buffer rb = { 0 }; // Default constructor for ring buffer
	PaStream *stream = nullptr;
	void *data;
	PaStreamParameters input_pars;
	PaStreamParameters output_pars;
	PaError err;

};