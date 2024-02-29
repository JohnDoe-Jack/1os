#include "serial.h"

#include "defines.h"

#define SERIAL_SCI_NUM 3

#define H8_3069F_SCI0 ((volatile struct h8_3069f_sci *)0xffffb0)
#define H8_3069F_SCI1 ((volatile struct h8_3069f_sci *)0xffffb8)
#define H8_3069F_SCI2 ((volatile struct h8_3069f_sci *)0xffffc0)

struct h8_3069f_sci
{
  volatile uint8 smr;   // Serial mode register
  volatile uint8 brr;   // Bit rate register
  volatile uint8 scr;   // Serial control register (Enable/Disable, Interrupt, etc.)
  volatile uint8 tdr;   // Transmit data register (Write)
  volatile uint8 ssr;   // Serial status register (If data is sent, received, etc.)
  volatile uint8 rdr;   // Receive data register (Read)
  volatile uint8 scmr;  // Smart card mode register
};

// Serial mode register

#define H8_3069F_SCI_SMR_CKS_PER1 (0 << 0)
#define H8_3069F_SCI_SMR_CKS_PER4 (1 << 0)
#define H8_3069F_SCI_SMR_CKS_PER16 (2 << 0)
#define H8_3069F_SCI_SMR_CKS_PER64 (3 << 0)
#define H8_3069F_SCI_SMR_MP (1 << 2)
#define H8_3069F_SCI_SMR_STOP (1 << 3)
#define H8_3069F_SCI_SMR_OE (1 << 4)
#define H8_3069F_SCI_SMR_PE (1 << 5)
#define H8_3069F_SCI_SMR_CHR (1 << 6)
#define H8_3069F_SCI_SMR_CA (1 << 7)

// Serial control register

#define H8_3069F_SCI_SCR_CKE0 (1 << 0)
#define H8_3069F_SCI_SCR_CKE1 (1 << 1)
#define H8_3069F_SCI_SCR_TEIE (1 << 2)
#define H8_3069F_SCI_SCR_MPIE (1 << 3)
#define H8_3069F_SCI_SCR_RE (1 << 4)   // Receive enable
#define H8_3069F_SCI_SCR_TE (1 << 5)   // Transmit enable
#define H8_3069F_SCI_SCR_RIE (1 << 6)  // Receive interrupt enable
#define H8_3069F_SCI_SCR_TIE (1 << 7)  // Transmit interrupt enable

// Serial status register

#define H8_3069F_SCI_SSR_MPBT (1 << 0)
#define H8_3069F_SCI_SSR_MPB (1 << 1)
#define H8_3069F_SCI_SSR_TEND (1 << 2)
#define H8_3069F_SCI_SSR_PER (1 << 3)
#define H8_3069F_SCI_SSR_FERERS (1 << 4)
#define H8_3069F_SCI_SSR_ORER (1 << 5)
#define H8_3069F_SCI_SSR_RDRF (1 << 6)  // Receive data register full
#define H8_3069F_SCI_SSR_TDRE (1 << 7)  // Transmit data register empty

static struct
{
  volatile struct h8_3069f_sci * sci;
} regs[SERIAL_SCI_NUM] = {
  {H8_3069F_SCI0},
  {H8_3069F_SCI1},
  {H8_3069F_SCI2},
};

// initialize device
int serial_init(int index)
{
  volatile struct h8_3069f_sci * sci = regs[index].sci;

  sci->scr = 0;
  sci->smr = 0;
  sci->brr = 64;                                         // 20MHz / (32*64) - 1 = 9600bps
  sci->scr = H8_3069F_SCI_SCR_RE | H8_3069F_SCI_SCR_TE;  // 1. Enable receive and transmit
  sci->ssr = 0;

  return 0;
}

// check if send action is enable

int serial_is_send_enable(int index)
{
  volatile struct h8_3069f_sci * sci = regs[index].sci;

  return (sci->ssr & H8_3069F_SCI_SSR_TDRE);
}

// send a byte
int serial_send_byte(int index, unsigned char b)
{
  volatile struct h8_3069f_sci * sci = regs[index].sci;

  while (!serial_is_send_enable(index))
    ;
  sci->tdr = b;
  sci->ssr &= ~H8_3069F_SCI_SSR_TDRE;

  return 0;
}
