/*
 * acquire_to_disk.c
 */

#include "acquire_to_disk.h"

#include <signal.h>
#include <stdio.h>

#include "ADQAPI.h"


// Handler for CTRL+C interrupts
static volatile int abort_acquisition = 0;

void sigint_handler(int signal)
{
    (void)signal;   // why is this dummy signal is needed (?)
    printf("Caught Ctrl-C. Aborting...\n");
    abort_acquisition = 1;
}

int configure_digitizer(void *control_unit)
{
    // Validate ADQAPI version
    switch (ADQAPI_ValidateVersion(ADQAPI_VERSION_MAJOR, ADQAPI_VERSION_MINOR))
    {
        case 0:
            // ADQAPI is compatible
            break;
        case -1:
            printf("ADQAPI version is incompatible. The application needs to be recompiled and relinked agains the installed ADQAPI.\n");
            return -1;
        case -2:
            printf("ADQAPI version is backwards compatible. It's suggested to recompile and relink the application agains the installed ADQAPI.\n");
            break;
    }

    // Initialize the handle to the ADQ control unit
    control_unit = CreateADQControlUnit();
    if (control_unit == NULL) {
        printf("[error] Failed to create handle to ADQ control unit");
        return -1;
    }

    return 0;

}

int acquire_to_disk()
{

    return 0;
}

int write_record_to_file(int channel, int record, void *buffer, size_t len)
{


    return 0;
}

int main()
{
    // Connect to signal handler for CTRL+C interrupts
    signal(SIGINT, sigint_handler);

    printf("Acquire to disk.\n");

    // Configure and initialize digitizer
    void *control_unit;
    configure_digitizer(control_unit);

    // Start acquisition
    acquire_to_disk();

    return 0;
}
