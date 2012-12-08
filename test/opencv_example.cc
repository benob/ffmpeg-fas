#include "ffmpeg_fas.h"
#include "cv.h"
#include "highgui.h"
#include <stdio.h>

int main (int argc, char **argv)
{
  fas_error_type video_error;
  fas_context_ref_type context;
  fas_raw_image_type image_buffer;
  
  if (argc < 2) {
    fprintf (stderr, "usage: %s <video_file>\n", argv[0]);
    return -1;
  }

  fas_initialize (FAS_FALSE, FAS_BGR24);
  
  fprintf(stderr, "%s\n",argv[1]);
  video_error = fas_open_video (&context, argv[1]);
  if (video_error != FAS_SUCCESS) {
      fprintf(stderr, "error: filed to open video\n");
      return 1;
  }
    
  while (fas_frame_available (context))
  {
      // read frame
      if (FAS_SUCCESS != fas_get_frame (context, &image_buffer)) {
          fprintf(stderr, "error: failed to get frame\n");
          return 1;
      }

      // convert to opencv image format
      cv::Mat opencv_image(image_buffer.height, image_buffer.width, CV_8UC3);
      for(int y=0; y<image_buffer.height; y++) {
          for (int x=0; x<image_buffer.width; x++) {
              opencv_image.at<cv::Vec3b>(y,x)[0]=image_buffer.data[y * image_buffer.bytes_per_line + x * 3 + 0];
              opencv_image.at<cv::Vec3b>(y,x)[1]=image_buffer.data[y * image_buffer.bytes_per_line + x * 3 + 1];
              opencv_image.at<cv::Vec3b>(y,x)[2]=image_buffer.data[y * image_buffer.bytes_per_line + x * 3 + 2];
          }
      } 

      // display image
      cv::imshow("frame", opencv_image);
      cv::waitKey(1);

      fas_free_frame (image_buffer);
      video_error = fas_step_forward (context);
  }

}
