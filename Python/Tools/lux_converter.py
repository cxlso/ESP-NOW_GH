'''
Input: analog_val
Ouput: a

Converts 12bits Analog values into Lux
'''

import math

# Constants
adc_max = 4095         # 12-bit ADC
v_ref = 3.3            # Reference voltage
r_known = 10000        # Ohms

# Ensure input is valid
if analog_val is None:
    a = None
else:
    voltage = analog_val * (v_ref / adc_max)

    if voltage <= 0 or voltage >= v_ref:
        a = 0
    else:
        r_ldr = (voltage * r_known) / (v_ref - voltage)
        a = 500 / ((r_ldr / 1000.0) ** 1.25)
