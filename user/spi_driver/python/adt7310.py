import spidev
import time
 
```
ADT7310 python driver

manual
https://www.analog.com/media/en/technical-documentation/data-sheets/ADT7310.pdf
https://www.analog.com/media/en/technical-documentation/application-notes/AN_892.pdf
https://www.analog.com/media/en/technical-documentation/user-guides/UG-047.pdf

```

spi = spidev.SpiDev()
spi.open(0,0)
spi.max_speed_hz = 1000000
 
def sign16(x):
    return ( -(x & 0x8000) | (x & 0x7fff) )
 
#main
spi.xfer2([0xff,0xff,0xff,0xff])
time.sleep(0.01)
# 0x0c : C3_5 001 C2 = 1
# reg 0x01 : b7 = 1 16bit mode
spi.xfer2([0x0c,0x80]) 
time.sleep(0.24)

# Dummy read. これをしないと正しく温度を測定できない.
for i in range(3):
    spi.xfer2([0x00,0x00])
    time.sleep(0.24)
 
for i in range(10):
    spi.xfer2([0x54])  # C6 = R / C3_5 010 / C2 = 1 : continus read.
    time.sleep(0.24)
    val = spi.xfer2([0x00,0x00])
    data = ((val[0]) << 8) | val[1] 
    if( data & 0x8000):
        # データが負数の場合
        data = - (data & 0x7fff)
    print (str(data*0.0078125) + "C")
    time.sleep(1)
spi.close()