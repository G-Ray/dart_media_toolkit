#include "dart_media_toolkit.h"

#include <libavformat/avformat.h>

// A very short-lived native function.
//
// For very short-lived functions, it is fine to call them on the main isolate.
// They will block the Dart execution while running the native function, so
// only do this for native functions which are guaranteed to be short-lived.
FFI_PLUGIN_EXPORT int64_t get_byte_offset(const char* filename, int64_t ts){
   AVFormatContext *fmt_ctx = NULL;
   int video_stream_index = -1;
   int ret;

   if ((ret = avformat_open_input(&fmt_ctx, filename, NULL, NULL)) < 0) {
       fprintf(stderr, "Could not open input file '%s'\n", filename);
       return -1;
   }

   if ((ret = avformat_find_stream_info(fmt_ctx, NULL)) < 0) {
       fprintf(stderr, "Failed to retrieve stream information\n");
       avformat_close_input(&fmt_ctx);
       return -1;
   }

   for (int i = 0; i < fmt_ctx->nb_streams; i++) {
       if (fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
           video_stream_index = i;
           break;
       }
   }

   if (video_stream_index == -1) {
       fprintf(stderr, "Could not find video stream\n");
       avformat_close_input(&fmt_ctx);
       return -1;
   }

   AVStream *video_stream = fmt_ctx->streams[video_stream_index];
   int64_t target_timestamp = av_rescale_q(ts * AV_TIME_BASE, AV_TIME_BASE_Q, video_stream->time_base);

   // Seek
   int rc = av_seek_frame(fmt_ctx, video_stream_index, target_timestamp, AVSEEK_FLAG_BACKWARD);
   if (rc < 0) {
      fprintf(stderr, "Could not seek\n");
       avformat_close_input(&fmt_ctx);
       return -1;
   }

   // Return current position
   return fmt_ctx->pb->pos;
}
