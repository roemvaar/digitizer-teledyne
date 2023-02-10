/*
 * continuous_acquisition_gpu.c
 */

#include "continuous_acquisition_gpu.h"

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

int main()
{
    // Connect to signal handler for CTRL+C interrupts
    signal(SIGINT, sigint_handler);

    printf("Continuous acquisition with GPU example\n");

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

    // Initialize the a handle to the ADQ control unit object
    // void *adq_control_unit = CreateADQControlUnit();

    return 0;
}
