/*
(c) Copyright 2013 Hewlett-Packard Development Company, L.P.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef LIB_PHOTO_SCALER_H
#define LIB_PHOTO_SCALER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "wtypes.h"

typedef unsigned char bool_t;

typedef struct float64_s
{
    uint32  decimal;
    uint32  fraction;
} float64_t;

typedef enum scaler_modes_e
{
    PSCALER_SCALE_UP=1,
    PSCALER_SCALE_DOWN=2,
    PSCALER_SCALE_MIXED_XUP=5,
    PSCALER_SCALE_MIXED_YUP=7,
    PSCALER_SCALE_MODE_INVALID
} scaler_mode_t;

typedef struct scaler_config_s
{
    uint16    iSrcWidth;        // input width (x-axis dimension)
    uint16    iSrcHeight;       // input height (y-axis dimension)

    uint16    iOutWidth;        // output width (x-axis dimension)
    uint16    iOutHeight;       // output height (y-axis dimension)

    uint8*    pSrcBuf;          // input buffers [plane]
    uint16    iSrcBufWidth;     // input buffer width (typically source width)

    uint8*    pOutBuf;          // output buffers [plane]
    uint16    iOutBufWidth;     // output buffer width

    uint8*    pTmpBuf;          // mixed axis temp buffer
    uint16    iTmpStripeSize;   // largest width * largest height               // scaler_setup_config

    float64_t fSrcStartRow;     // first input row as a float                   // scaler_calculate_rows
    uint16    iSrcStartRow;     // first input row of this slice                // scaler_calculate_rows
    uint16    iSrcEndRow;       // last input row of this slice                 // pscaler_calculate_rows

    uint16    iOutStartRow;     // first output row of this slice               // pscaler_calculate_rows
    uint16    iOutEndRow;       // last output row of this slice                // pscaler_calculate_rows

    float64_t fSrcStartColumn;  // first input column as a float
    uint16    iSrcStartColumn;  // first input column of this slice
    uint16    iSrcEndColumn;    // last input column of this slice

    uint16    iOutStartColumn;  // first output column of this slice
    uint16    iOutEndColumn;    // last output column of this slice

    float64_t fXfactor;         // x_factor_int & x_factor_fract                // pscaler_setup_config
    float64_t fXfactorInv;      // x_factor_inv_int & x_factor_inv_fract        // pscaler_setup_config
    float64_t fYfactor;         // y_factor_int & y_factor_fract                // scaler_setup_config
    float64_t fYfactorInv;      // y_factor_inv_int & y_factor_inv_fract        // scaler_setup_config

    scaler_mode_t scaleMode;    // scale mode for the current image             // scaler_setup_config

} scaler_config_t;

extern void LIB_PHOTO_SCALER_make_image_scaler_tables(uint16 image_input_width, 
                                                  uint16 image_input_buf_width, 
                                                  uint16 image_output_width,
                                                  uint16 image_output_buf_width,
                                                  uint16 image_input_height, 
                                                  uint16 image_output_height,
                                                  scaler_config_t* pscaler_config);
extern void LIB_PHOTO_SCALER_calculate_scaling_rows(uint16 start_output_row_number,
                                                uint16 end_output_row_number,
                                                void   *tables_ptr,
                                                uint16 *start_input_row_number,
                                                uint16 *end_input_row_number,
                                                uint16 *num_output_rows_generated,
                                                uint16 *num_rows_offset_to_start_output_row,
                                                uint32 *mixed_axis_temp_buffer_size_needed);
extern void LIB_PHOTO_SCALER_scale_image_data(uint8   *input_plane,
                                              uint16 start_input_row_number,
                                              uint16 end_input_row_number,
                                              uint16 start_output_row_number,
                                              void   *tables_ptr,
                                              uint8  *scaled_output_plane,
                                              uint8  *temp_buffer_for_mixed_axis_scaling);

#ifdef __cplusplus
}
#endif

#endif  /* LIB_PHOTO_SCALER_H */
