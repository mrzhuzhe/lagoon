# Linux tty setup
```
# show config 
sudo stty -F /dev/ttyUSB0 -a

# baud rate to 38400, 8 bits, 1 stop bit, no parity:
chmod 666 /dev/ttyUSB0 
stty -F /dev/ttyUSB0 38400 cs8 -cstopb -parenb -echo -icanon -onlcr

# USB port
# USB cdc https://github.com/libopencm3/libopencm3-examples/tree/master/examples/stm32/f1/stm32-maple/usb_cdcacm
chmod 666 /dev/ttyACM0 
stty -F /dev/ttyACM0  115200  cs8 -cstopb -parenb -echo -icanon -onlcr


# USB spi
chmod 666 /dev/ttyACM0 
stty -F /dev/ttyACM0  2400  cs8 -cstopb -parenb -echo -icanon -onlcr
```


# Debug stlink set up

```

st-util -p 4500

(arm-none-eabi-gdb) target extended-remote localhost:4500

(arm-none-eabi-gdb) file rtos-template.elf

```