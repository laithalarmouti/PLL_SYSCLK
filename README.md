# STM32F4 Dynamic System Clock Configuration & UART Debug Output

This STM32F4 project demonstrates **dynamic system clock configuration at runtime**, allowing the user to select between **50 MHz, 80 MHz, and 100 MHz system clock frequencies** via code.

 The configured clock frequencies (SYSCLK, HCLK, PCLK1, PCLK2) are printed to the serial console via **USART2** (TX=PA2, RX=PA3) at **115200 baud**.

Includes manual **HAL MSP initialization**, **SysTick configuration**, and **UART2 initialization**.

---

##  Features

- Selects system clock frequency at runtime:
  - 50 MHz
  - 80 MHz
  - 100 MHz
- Configures RCC PLL parameters based on selected frequency
- Initializes **USART2** for debug printout at **115200 baud**
- Prints actual clock values:
  - `SYSCLK`
  - `HCLK`
  - `PCLK1`
  - `PCLK2`
- Manually configures **SysTick** to generate 1ms ticks
- Enables **system exceptions** (Usage Fault, Bus Fault, Memory Fault)
- Performs low-level GPIO/IRQ configuration in **HAL_MspInit**

---

##  Hardware Requirements

- STM32F4 series microcontroller (tested on **STM32F411RE Nucleo**)
- USART2 connected:
  - **TX → PA2**
  - **RX → PA3**
- USB-UART converter or ST-Link Virtual COM for serial monitoring

---

##  How It Works

 The `SystemClock_Config()` function dynamically configures the PLL settings and RCC clock dividers based on a selected clock frequency (passed as argument).

 After initialization:
1. Prints current system clock values via **UART2**.
2. Configures **SysTick** to tick every 1ms based on HCLK.
3. Enables system-level fault exceptions.
4. Initializes GPIO for USART2 and sets up its interrupt.

---
##  Example UART Output

SYSCLK : 50000000
HCLK : 50000000
PCLK1 : 25000000
PCLK2 : 50000000
