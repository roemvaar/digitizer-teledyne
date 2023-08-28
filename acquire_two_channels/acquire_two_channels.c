// /*
//  * acquire_two_channels.c
//  */

// #include "acquire_two_channels.h"

// #include <inttypes.h>
// #include <signal.h>
// #include <stdbool.h>
// #include <stdio.h>

// #include "ADQAPI.h"

// // Handler for CTRL+C interrupts
// static volatile int abort_acquisition = 0;

// void sigint_handler(int signal)
// {
//     (void)signal;   // why is this dummy signal is needed (?)
//     printf("Caught Ctrl-C. Aborting...\n");
//     abort_acquisition = 1;
// }

// #if (WRITE_TO_FILE == 1)
// static int WriteRecordToFile(int channel, int record, void *buf, size_t len)
// {
//   char filename[256] = "";
//   sprintf(filename, "%s_ch%d_r%d.bin", BASE_FILENAME, channel, record);

//   FILE *fp = fopen(filename, "wb");
//   if (fp == NULL)
//   {
//     printf("Failed to open the file '%s' for writing.\n", filename);
//     return -1;
//   }

//   size_t bytes_written = fwrite(buf, 1, len, fp);
//   if (bytes_written != len)
//   {
//     printf("Failed to write %zu bytes to the file '%s', wrote %zu bytes.\n", len, filename,
//            bytes_written);
//     fclose(fp);
//     return -1;
//   }

//   fclose(fp);
//   return 0;
// }
// #endif

// // int configure_digitizer(void *control_unit)
// // {
// //     // Validate ADQAPI version
// //     switch (ADQAPI_ValidateVersion(ADQAPI_VERSION_MAJOR, ADQAPI_VERSION_MINOR))
// //     {
// //         case 0:
// //             // ADQAPI is compatible
// //             break;
// //         case -1:
// //             printf("ADQAPI version is incompatible. The application needs to be recompiled and relinked agains the installed ADQAPI.\n");
// //             return -1;
// //         case -2:
// //             printf("ADQAPI version is backwards compatible. It's suggested to recompile and relink the application agains the installed ADQAPI.\n");
// //             break;
// //     }

// //     // Initialize the handle to the ADQ control unit
// //     control_unit = CreateADQControlUnit();
// //     if (control_unit == NULL) {
// //         printf("[error] Failed to create handle to ADQ control unit");
// //         return -1;
// //     }

// //     return 0;

// // }

// // int acquire_two_channels()
// // {

// //     return 0;
// // }

// int write_record_to_file(int channel, int record, void *buffer, size_t len)
// {


//     return 0;
// }

// int main()
// {
//     // Connect to signal handler for CTRL+C interrupts
//     signal(SIGINT, sigint_handler);

//     printf("Acquire two channels.\n");

//     // Configure and initialize digitizer
//     // configure_digitizer(control_unit);
//     void *control_unit = CreateADQControlUnit();
//     if (control_unit == NULL)
//     {
//         printf("Failed to create a handle to an ADQ control unit object.\n");
//         return -1;
//     }

//     int device_to_open_idx = 0;

//     printf("Configuring device... ");
//     if (ADQControlUnit_SetupDevice(control_unit, device_to_open_idx))
//     {
//         printf("success.\n");
//     }
//     else
//     {
//         printf("failed.\n");
//         goto exit;
//     }

//     // Device ids for the ADQ_* functions start at 1, representing the first
//     // device listed by ADQControlUnit_ListDevices().
//     int adq_num = 1;

//     // Initialize parameters.
//     struct ADQParameters adq;
//     if (ADQ_InitializeParameters(control_unit, adq_num, ADQ_PARAMETER_ID_TOP, &adq) != sizeof(adq))
//     {
//         printf("Failed to initialize digitizer parameters.\n");
//         goto exit;
//     }

//     // Cap the number of active channels to the number of available channels.
//     int nof_active_channels = NOF_ACTIVE_CHANNELS;
//     if (nof_active_channels > adq.constant.nof_channels)
//     {
//         printf("Limiting the number of active channels to %d (maximum available).\n",
//             adq.constant.nof_channels);
//         nof_active_channels = adq.constant.nof_channels;
//     }
    
//     // Modify parameters (values from the header file "acquire_two_channels.h").
//     adq.afe.channel[0].dc_offset = CH0_DC_OFFSET;
//     adq.afe.channel[1].dc_offset = CH1_DC_OFFSET;

//     adq.signal_processing.dbs.channel[0].level = CH0_DBS_LEVEL;
//     adq.signal_processing.dbs.channel[0].bypass = CH0_DBS_BYPASS;
//     adq.signal_processing.dbs.channel[1].level = CH1_DBS_LEVEL;
//     adq.signal_processing.dbs.channel[1].bypass = CH1_DBS_BYPASS;
//     adq.signal_processing.sample_skip.channel[0].skip_factor = CH0_SAMPLE_SKIP_FACTOR;
//     adq.signal_processing.sample_skip.channel[1].skip_factor = CH1_SAMPLE_SKIP_FACTOR;

//     adq.test_pattern.channel[0].source = CH0_TEST_PATTERN_SOURCE;
//     adq.test_pattern.channel[1].source = CH1_TEST_PATTERN_SOURCE;

//     adq.event_source.level.channel[0].level = CH0_LT_LEVEL;
//     adq.event_source.level.channel[0].arm_hysteresis = CH0_LT_ARM_HYSTERESIS;
//     adq.event_source.level.channel[1].level = CH1_LT_LEVEL;
//     adq.event_source.level.channel[1].arm_hysteresis = CH1_LT_ARM_HYSTERESIS;

//     adq.event_source.periodic.period = PERIODIC_EVENT_SOURCE_PERIOD;
//     adq.event_source.periodic.frequency = PERIODIC_EVENT_SOURCE_FREQUENCY;

//     adq.event_source.port[ADQ_PORT_TRIG].threshold = TRIGGER_THRESHOLD_V;
//     adq.event_source.port[ADQ_PORT_SYNC].threshold = TRIGGER_THRESHOLD_V;

//     // Configure data acquisition for channel 0.
//     adq.acquisition.channel[0].nof_records = NOF_RECORDS_PER_BUFFER * NOF_BUFFERS_TO_RECEIVE;
//     adq.acquisition.channel[0].record_length = CH0_RECORD_LEN;
//     adq.acquisition.channel[0].trigger_source = CH0_TRIGGER_SOURCE;
//     adq.acquisition.channel[0].trigger_edge = CH0_TRIGGER_EDGE;
//     adq.acquisition.channel[0].horizontal_offset = CH0_HORIZONTAL_OFFSET;

//     // Configure data acquisition for channel 1.
//     if (nof_active_channels > 1)
//     {
//         adq.acquisition.channel[1].nof_records = NOF_RECORDS_PER_BUFFER * NOF_BUFFERS_TO_RECEIVE;
//         adq.acquisition.channel[1].record_length = CH1_RECORD_LEN;
//         adq.acquisition.channel[1].trigger_source = CH1_TRIGGER_SOURCE;
//         adq.acquisition.channel[1].trigger_edge = CH1_TRIGGER_EDGE;
//         adq.acquisition.channel[1].horizontal_offset = CH1_HORIZONTAL_OFFSET;
//     }

//     // Configure data transfer parameters for channel 0.
//     adq.transfer.channel[0].record_size = sizeof(int16_t) * adq.acquisition.channel[0].record_length;
//     adq.transfer.channel[0].record_length_infinite_enabled = 0;
//     adq.transfer.channel[0].record_buffer_size = NOF_RECORDS_PER_BUFFER * adq.transfer.channel[0].record_size;
//     adq.transfer.channel[0].metadata_buffer_size = NOF_RECORDS_PER_BUFFER * sizeof(struct ADQGen4RecordHeader);
//     adq.transfer.channel[0].metadata_enabled = 1;
//     adq.transfer.channel[0].nof_buffers = NOF_TRANSFER_BUFFERS;

//     // Configure data transfer parameters for channel 1.
//     if (nof_active_channels > 1)
//     {
//         adq.transfer.channel[1].record_size = sizeof(int16_t) * adq.acquisition.channel[1].record_length;
//         adq.transfer.channel[1].record_length_infinite_enabled = 0;
//         adq.transfer.channel[1].record_buffer_size = NOF_RECORDS_PER_BUFFER * adq.transfer.channel[1].record_size;
//         adq.transfer.channel[1].metadata_buffer_size = NOF_RECORDS_PER_BUFFER * sizeof(struct ADQGen4RecordHeader);
//         adq.transfer.channel[1].metadata_enabled = 1;
//         adq.transfer.channel[1].nof_buffers = NOF_TRANSFER_BUFFERS;
//     }

//     printf("Configuring digitizer parameters... ");
//     if (ADQ_SetParameters(control_unit, adq_num, &adq) == sizeof(adq))
//     {
//         printf("success.\n");
//     }
//     else
//     {
//         printf("failed.\n");
//         goto exit;
//     }
    
//     // // Start the data acquisition
//     // acquire_two_channels();
//      printf("Start acquiring data... ");
//     if (ADQ_StartDataAcquisition(control_unit, adq_num) == ADQ_EOK)
//     {
//         printf("success.\n");
//     }
//     else
//     {
//         printf("failed.\n");
//         goto exit;
//     }

//     // Send software triggers. This structure sends more triggers than required
//     // since all channels share a common source.
//     for (int ch = 0; ch < nof_active_channels; ++ch) {
//         if (adq.acquisition.channel[ch].trigger_source == ADQ_EVENT_SOURCE_SOFTWARE) {
//             if (adq.acquisition.channel[0].nof_records != 0) {
//                 printf("Generating software events on channel %d.\n", ch);
//             }

//             for (int i = 0; i < adq.acquisition.channel[0].nof_records; ++i) {
//                 if(ADQ_SWTrig(control_unit, adq_num) != ADQ_EOK) {
//                     printf("Error: SWTrig failed.\n");
//                     goto exit;
//                 }
//             }
//         }
//     }

//     // Data readout loop
//     bool done = false;
//     int nof_received_records[ADQ_MAX_NOF_CHANNELS] = {0};
//     while (!done && !abort_acquisition)
//     {
//         struct ADQGen4Record *record = NULL;
//         int channel = ADQ_ANY_CHANNEL;
//         /* Wait for a record buffer. */
//         int64_t bytes_received = ADQ_WaitForRecordBuffer(control_unit, adq_num, &channel,
//                                                         (void **)(&record), WAIT_TIMEOUT_MS, NULL);
//         /* Negative values are errors. */
//         if (bytes_received == ADQ_EAGAIN)
//         {
//         printf("Timeout while waiting %d ms for new record buffers.\n", WAIT_TIMEOUT_MS);
//         continue;
//         }
//         else if (bytes_received < 0)
//         {
//         printf("Error: %" PRId64 ".\n", bytes_received);
//         break;
//         }

//         /* Process the data. */
//         printf("Got record %d w/ %" PRId64 " bytes, channel %d.\n",
//             nof_received_records[channel], bytes_received, channel);

// #if (WRITE_TO_FILE == 1)
//         WriteRecordToFile(channel, nof_received_records[channel], (int16_t *)record->data, bytes_received);
//         printf("First 8 samples:\n");
//         for (int i = 0; i < 10; ++i)
//         {
//         if (i > 0)
//             printf(", ");
//         printf("%d", *((int16_t *)record->data + i));
//         }
//         printf("\n\n");
// #endif

//         // Return the buffer to the API.
//         int result = ADQ_ReturnRecordBuffer(control_unit, adq_num, channel, record);
//         if (result != ADQ_EOK) {
//             printf("Failed to return a record buffer, code %d.\n", result);
//             break;
//         }

//         // Check if the acquisition should end.
//         ++nof_received_records[channel];
//         done = true;
//         for (int ch = 0; ch < nof_active_channels; ++ch) {
//             if (adq.acquisition.channel[ch].nof_records != nof_received_records[ch]) {
//                 done = false;
//             }
//         }
//     }

//     // Stop the data acquisition process.
//     printf("Stop acquiring data... ");
//     int result = ADQ_StopDataAcquisition(control_unit, adq_num);
//     switch (result)
//     {
//     case ADQ_EOK:
//     case ADQ_EINTERRUPTED:
//         printf("success.\n");
//         break;
//     default:
//         printf("failed, code %d.\n", result);
//         break;
//     }

// exit:
//     /* Delete the control unit object and the memory allocated by this application. */
//     DeleteADQControlUnit(control_unit);
//     printf("Exiting the application.\n");
//     fflush(stdout);
//     return 0;
// }


/*
 * Copyright 2020 Teledyne Signal Processing Devices Sweden AB
 */

#include "acquire_two_channels.h"

#include "ADQAPI.h"
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <signal.h>

// Handler for CTRL+C interrupts
static volatile int abort_acquisition = 0;
void sigint_handler(int dummy)
{
  (void)dummy;
  printf("Caught Ctrl-C. Aborting..\n");
  abort_acquisition = 1;
}

#if (WRITE_TO_FILE == 1)
static int WriteRecordToFile(int channel, int record, void *buf, size_t len)
{
  char filename[256] = "";
  sprintf(filename, "%s_ch%d_r%d.bin", BASE_FILENAME, channel, record);

  FILE *fp = fopen(filename, "wb");
  if (fp == NULL)
  {
    printf("Failed to open the file '%s' for writing.\n", filename);
    return -1;
  }

  size_t bytes_written = fwrite(buf, 1, len, fp);
  if (bytes_written != len)
  {
    printf("Failed to write %zu bytes to the file '%s', wrote %zu bytes.\n", len, filename,
           bytes_written);
    fclose(fp);
    return -1;
  }

  fclose(fp);
  return 0;
}
#endif

int main()
{
  // Connect handler for CTRL+C interrupts
  signal(SIGINT, sigint_handler);

  /* Validate ADQAPI version. */
  switch (ADQAPI_ValidateVersion(ADQAPI_VERSION_MAJOR, ADQAPI_VERSION_MINOR))
  {
  case 0:
    // ADQAPI is compatible
    break;
  case -1:
    printf("ADQAPI version is incompatible. The application needs to be recompiled and relinked against the installed ADQAPI.\n");
    return -1;
  case -2:
    printf("ADQAPI version is backwards compatible. It's suggested to recompile and relink the application against the installed ADQAPI.\n");
    break;
  }

  /* Initialize the a handle to the ADQ control unit object. */
  void *adq_cu = CreateADQControlUnit();
  if (adq_cu == NULL)
  {
    printf("Failed to create a handle to an ADQ control unit object.\n");
    return -1;
  }

  /* Enable the error trace log. */
  ADQControlUnit_EnableErrorTrace(adq_cu, LOG_LEVEL_INFO, ".");

  /* List the available devices connected to the host computer. */
  struct ADQInfoListEntry *adq_list = NULL;
  unsigned int nof_devices = 0;
  if (!ADQControlUnit_ListDevices(adq_cu, &adq_list, &nof_devices))
  {
    printf("ListDevices failed!\n");
    return -1;
  }

  if (nof_devices == 0)
  {
    printf("No device connected.\n");
    goto exit;
  }
  else if (nof_devices != 1)
  {
    printf("Only one ADQ is supported by this example.\n");
    goto exit;
  }

  /* Since this example only supports one device, we always open the device at
     list index zero. */
  int device_to_open_idx = 0;

  printf("Configuring device... ");
  if (ADQControlUnit_SetupDevice(adq_cu, device_to_open_idx))
  {
    printf("success.\n");
  }
  else
  {
    printf("failed.\n");
    goto exit;
  }

  /* Device ids for the ADQ_* functions start at 1, representing the first
     device listed by ADQControlUnit_ListDevices(). */
  int adq_num = 1;

  /* Initialize parameters. */
  struct ADQParameters adq;
  if (ADQ_InitializeParameters(adq_cu, adq_num, ADQ_PARAMETER_ID_TOP, &adq) != sizeof(adq))
  {
    printf("Failed to initialize digitizer parameters.\n");
    goto exit;
  }

  /* Cap the number of active channels to the number of available channels. */
  int nof_active_channels = NOF_ACTIVE_CHANNELS;
  if (nof_active_channels > adq.constant.nof_channels)
  {
    printf("Limiting the number of active channels to %d (maximum available).\n",
           adq.constant.nof_channels);
    nof_active_channels = adq.constant.nof_channels;
  }

  /* Modify parameters (values from the header file "settings.h"). */
  adq.afe.channel[0].dc_offset = CH0_DC_OFFSET;
  adq.afe.channel[1].dc_offset = CH1_DC_OFFSET;

  adq.signal_processing.dbs.channel[0].level = CH0_DBS_LEVEL;
  adq.signal_processing.dbs.channel[0].bypass = CH0_DBS_BYPASS;
  adq.signal_processing.dbs.channel[1].level = CH1_DBS_LEVEL;
  adq.signal_processing.dbs.channel[1].bypass = CH1_DBS_BYPASS;
  adq.signal_processing.sample_skip.channel[0].skip_factor = CH0_SAMPLE_SKIP_FACTOR;
  adq.signal_processing.sample_skip.channel[1].skip_factor = CH1_SAMPLE_SKIP_FACTOR;

  adq.test_pattern.channel[0].source = CH0_TEST_PATTERN_SOURCE;
  adq.test_pattern.channel[1].source = CH1_TEST_PATTERN_SOURCE;

  adq.event_source.level.channel[0].level = CH0_LT_LEVEL;
  adq.event_source.level.channel[0].arm_hysteresis = CH0_LT_ARM_HYSTERESIS;
  adq.event_source.level.channel[1].level = CH1_LT_LEVEL;
  adq.event_source.level.channel[1].arm_hysteresis = CH1_LT_ARM_HYSTERESIS;

  adq.event_source.periodic.period = PERIODIC_EVENT_SOURCE_PERIOD;
  adq.event_source.periodic.frequency = PERIODIC_EVENT_SOURCE_FREQUENCY;

  adq.event_source.port[ADQ_PORT_TRIG].threshold = TRIGGER_THRESHOLD_V;
  adq.event_source.port[ADQ_PORT_SYNC].threshold = TRIGGER_THRESHOLD_V;

  /* Configure data acquisition for channel 0. */
  adq.acquisition.channel[0].nof_records = NOF_RECORDS_PER_BUFFER * NOF_BUFFERS_TO_RECEIVE;
  adq.acquisition.channel[0].record_length = CH0_RECORD_LEN;
  adq.acquisition.channel[0].trigger_source = CH0_TRIGGER_SOURCE;
  adq.acquisition.channel[0].trigger_edge = CH0_TRIGGER_EDGE;
  adq.acquisition.channel[0].horizontal_offset = CH0_HORIZONTAL_OFFSET;

  /* Configure data acquisition for channel 1. */
  if (nof_active_channels > 1)
  {
    adq.acquisition.channel[1].nof_records = NOF_RECORDS_PER_BUFFER * NOF_BUFFERS_TO_RECEIVE;
    adq.acquisition.channel[1].record_length = CH1_RECORD_LEN;
    adq.acquisition.channel[1].trigger_source = CH1_TRIGGER_SOURCE;
    adq.acquisition.channel[1].trigger_edge = CH1_TRIGGER_EDGE;
    adq.acquisition.channel[1].horizontal_offset = CH1_HORIZONTAL_OFFSET;
  }

  /* Configure data transfer parameters for channel 0. */
  adq.transfer.channel[0].record_size = sizeof(int16_t) * adq.acquisition.channel[0].record_length;
  adq.transfer.channel[0].record_length_infinite_enabled = 0;
  adq.transfer.channel[0].record_buffer_size = NOF_RECORDS_PER_BUFFER * adq.transfer.channel[0].record_size;
  adq.transfer.channel[0].metadata_buffer_size = NOF_RECORDS_PER_BUFFER * sizeof(struct ADQGen4RecordHeader);
  adq.transfer.channel[0].metadata_enabled = 1;
  adq.transfer.channel[0].nof_buffers = NOF_TRANSFER_BUFFERS;

  /* Configure data transfer parameters for channel 1. */
  if (nof_active_channels > 1)
  {
    adq.transfer.channel[1].record_size = sizeof(int16_t) * adq.acquisition.channel[1].record_length;
    adq.transfer.channel[1].record_length_infinite_enabled = 0;
    adq.transfer.channel[1].record_buffer_size = NOF_RECORDS_PER_BUFFER * adq.transfer.channel[1].record_size;
    adq.transfer.channel[1].metadata_buffer_size = NOF_RECORDS_PER_BUFFER * sizeof(struct ADQGen4RecordHeader);
    adq.transfer.channel[1].metadata_enabled = 1;
    adq.transfer.channel[1].nof_buffers = NOF_TRANSFER_BUFFERS;
  }

  printf("Configuring digitizer parameters... ");
  if (ADQ_SetParameters(adq_cu, adq_num, &adq) == sizeof(adq))
  {
    printf("success.\n");
  }
  else
  {
    printf("failed.\n");
    goto exit;
  }

  /* Start the data acquisition. */
  printf("Start acquiring data... ");
  if (ADQ_StartDataAcquisition(adq_cu, adq_num) == ADQ_EOK)
  {
    printf("success.\n");
  }
  else
  {
    printf("failed.\n");
    goto exit;
  }

  /* Send software triggers. This structure sends more triggers than required
     since all channels share a common source. */
  for (int ch = 0; ch < nof_active_channels; ++ch)
  {
    if (adq.acquisition.channel[ch].trigger_source == ADQ_EVENT_SOURCE_SOFTWARE)
    {
      if (adq.acquisition.channel[0].nof_records != 0)
        printf("Generating software events on channel %d.\n", ch);

      for (int i = 0; i < adq.acquisition.channel[0].nof_records; ++i)
      {
        if(ADQ_SWTrig(adq_cu, adq_num) != ADQ_EOK)
        {
          printf("Error: SWTrig failed.\n");
          goto exit;
        }
      }
    }
  }

  /* Data readout loop. */
  bool done = false;
  int nof_received_records[ADQ_MAX_NOF_CHANNELS] = {0};
  while (!done && !abort_acquisition)
  {
    struct ADQGen4Record *record = NULL;
    int channel = ADQ_ANY_CHANNEL;
    /* Wait for a record buffer. */
    int64_t bytes_received = ADQ_WaitForRecordBuffer(adq_cu, adq_num, &channel,
                                                     (void **)(&record), WAIT_TIMEOUT_MS, NULL);
    /* Negative values are errors. */
    if (bytes_received == ADQ_EAGAIN)
    {
      printf("Timeout while waiting %d ms for new record buffers.\n", WAIT_TIMEOUT_MS);
      continue;
    }
    else if (bytes_received < 0)
    {
      printf("Error: %" PRId64 ".\n", bytes_received);
      break;
    }

    /* Process the data. */
    printf("Got record %d w/ %" PRId64 " bytes, channel %d.\n",
           nof_received_records[channel], bytes_received, channel);

#if (WRITE_TO_FILE == 1)
    WriteRecordToFile(channel, nof_received_records[channel], (int16_t *)record->data, bytes_received);
    printf("First 8 samples:\n");
    for (int i = 0; i < 10; ++i)
    {
      if (i > 0)
        printf(", ");
      printf("%d", *((int16_t *)record->data + i));
    }
    printf("\n\n");
#endif

    /* Return the buffer to the API. */
    int result = ADQ_ReturnRecordBuffer(adq_cu, adq_num, channel, record);
    if (result != ADQ_EOK)
    {
      printf("Failed to return a record buffer, code %d.\n", result);
      break;
    }

    /* Check if the acquisition should end. */
    ++nof_received_records[channel];
    done = true;
    for (int ch = 0; ch < nof_active_channels; ++ch)
    {
      if (adq.acquisition.channel[ch].nof_records != nof_received_records[ch])
        done = false;
    }
  }

  /* Stop the data acquisition process. */
  printf("Stop acquiring data... ");
  int result = ADQ_StopDataAcquisition(adq_cu, adq_num);
  switch (result)
  {
  case ADQ_EOK:
  case ADQ_EINTERRUPTED:
    printf("success.\n");
    break;
  default:
    printf("failed, code %d.\n", result);
    break;
  }

exit:
  /* Delete the control unit object and the memory allocated by this application. */
  DeleteADQControlUnit(adq_cu);
  printf("Exiting the application.\n");
  fflush(stdout);
  return 0;
}
