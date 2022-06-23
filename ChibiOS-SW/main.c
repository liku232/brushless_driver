/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

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

#include "ch.h"
#include "hal.h"
#include "chprintf.h" //to get rid of compiler warnings
#include "stdlib.h" //to get rid of compiler warnings
#include "shell.h"

#define TIMFREQ 1000000
#define PWMFREQ 6000
#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)

void ModifyDeadtime(TIM_TypeDef * TIMP, uint16_t dt);

static void cmd_dt(BaseSequentialStream *chp, int argc, char *argv[]) {
  const char * const usage = "Usage: dt NUMBER\r\n";
  volatile uint16_t nr;

  if (argc != 1) {
    chprintf(chp, usage);
    return;
  }
  nr = (uint16_t)atoi(argv[0]);
  chprintf(chp, "This is a Test\r\n");
  chprintf(chp, "You entered  : %i \r\n", nr);
  ModifyDeadtime(TIM1, nr);
}

static void cmd_dc(BaseSequentialStream *chp, int argc, char *argv[]) {
  const char * const usage = "Usage: dt NUMBER\r\n";
  volatile uint16_t nr;

  if (argc != 1) {
    chprintf(chp, usage);
    return;
  }
  nr = (uint16_t)atoi(argv[0]);
  chprintf(chp, "This is a Test\r\n");
  chprintf(chp, "You entered  : %i \r\n", nr);
  pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, nr*100));
}

static void pwmpcb(PWMDriver *pwmp) {

  (void)pwmp;

}

static void pwmc1cb(PWMDriver *pwmp) {

  (void)pwmp;
  //palSetPad(GPIOD, GPIOD_LED5);
}

static PWMConfig pwmcfg = {
  TIMFREQ,                                    /* 1MHz PWM clock frequency.   */
  PWMFREQ,                                    /* Initial PWM period     */
  pwmpcb,
  {
   {PWM_OUTPUT_ACTIVE_HIGH, pwmc1cb},
   {PWM_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_DISABLED, NULL}
  },
  0,
  0
};



static const ShellCommand commands[] = {
  {"dt", cmd_dt},
  {"dc", cmd_dc},
  {NULL, NULL}
};

static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream *)&SD2,
  commands
};

void ModifyDeadtime(TIM_TypeDef * TIMP, uint16_t dt){
  uint16_t bdtr = (TIMP->BDTR) & 0xFF80;  //Mask out DTG[0..6] Bits
  bdtr |= dt; //Bits 0..4 or 0..5 or 0..6 are deadtime
  TIMP->BDTR = bdtr;
}
void ModifyDeadtimeSetup(TIM_TypeDef * TIMP, uint16_t dtf){
  uint16_t bdtr, cr1;
  switch (dtf) {
  case 0:
    dtf = 0;
    bdtr = (TIMP->BDTR) & 0xFF00;  //Mask out DTG[0..7] Bits
    bdtr |= dtf;
    TIMP->BDTR = bdtr;
    break;
  case 1:
    dtf = (1<<7); //Bit 7 is set
    bdtr = (TIMP->BDTR) & 0xFF00;  //Mask out DTG[0..7] Bits
    bdtr |= dtf;
    TIMP->BDTR = bdtr;
    break;
  case 2:
    dtf = (3<<6); //Bits 6,7 set
    bdtr = (TIMP->BDTR) & 0xFF00;  //Mask out DTG[0..7] Bits
    bdtr |= dtf;
    TIMP->BDTR = bdtr;
    break;
  case 3:
    dtf = (7<<5);  //Bits 5,6,7 set
    bdtr = (TIMP->BDTR) & 0xFF00;  //Mask out DTG[0..7] Bits
    bdtr |= dtf;
    TIMP->BDTR = bdtr;
    break;
  case 4:
    cr1 = (TIMP->CR1) & 0xFCFF;  //Mask out CKG[8..9] Bits
    TIMP->CR1 = cr1;
    break;
  case 5:
    dtf = (1<<8);  //Bit 8 set
    cr1 = (TIMP->CR1) & 0xFCFF;  //Mask out CKG[8..9] Bits
    cr1 |= dtf;
    TIMP->CR1 = cr1;
    break;
  case 6:
    dtf = (1<<9);  //Bit 9 set
    cr1 = (TIMP->CR1) & 0xFCFF;  //Mask out CKG[8..9] Bits
    cr1 |= dtf;
    TIMP->CR1 = cr1;
    break;
  }
}

/*
 * Application entry point.
 */
int main(void) {
  thread_t *shelltp = NULL;

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();
  shellInit();


  sdStart(&SD2, NULL);
  chprintf((BaseSequentialStream *)&SD2, "ChibiOS Disco F446 Shell v0.1\r\n");

  /*
   * Initializes the PWM driver 2 and ICU driver 3.
   * GPIOA8 is the PWM output.
   * GPIOC6 is the ICU input.
   * The two pins have to be externally connected together.
   */

  pwmStart(&PWMD1, &pwmcfg);
  pwmEnablePeriodicNotification(&PWMD1);
  palSetPadMode(GPIOA, 8, PAL_MODE_ALTERNATE(1));
  palSetPadMode(GPIOA, 7, PAL_MODE_ALTERNATE(1));

  palSetPadMode(GPIOA, 9, PAL_MODE_ALTERNATE(1));
  palSetPadMode(GPIOB, 0, PAL_MODE_ALTERNATE(1));
  chThdSleepMilliseconds(2000);

  /*
   * Starts the PWM channel 0 using 75% duty cycle.
   */
  pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 7500));
  pwmEnableChannelNotification(&PWMD1, 0);
  TIM1->CCER |= TIM_CCER_CC1NE;
  ModifyDeadtimeSetup(TIM1, 3);
  ModifyDeadtime(TIM1, 0b0000000000011111);

  /*
     * Starts the PWM channel 1 using 75% duty cycle.
     */
  pwmEnableChannel(&PWMD1, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 7500));
  pwmEnableChannelNotification(&PWMD1, 1);
  TIM1->CCER |= TIM_CCER_CC2NE;

  /*
   * Disables channel 0 and stops the drivers.
   */
  //pwmDisableChannel(&PWMD1, 0);
  //pwmStop(&PWMD1);

  /*
   * Normal main() thread activity, in this demo it does nothing.
   */
  while (true) {
    if (!shelltp) {
              /* Spawns a new shell.*/
            thread_t *shelltp = chThdCreateFromHeap(NULL, SHELL_WA_SIZE,
                                                    "shell", NORMALPRIO + 1,
                                                    shellThread, (void *)&shell_cfg1);
            chThdWait(shelltp);               /* Waiting termination.             */
          }
      if (chThdTerminatedX(shelltp)) {
         /* Recovers memory of the previous shell.*/
         chThdRelease(shelltp);
         shelltp = NULL;
       }
    chThdSleepMilliseconds(500);
  }
}
