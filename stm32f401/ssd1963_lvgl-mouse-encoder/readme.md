
``` c

    SSD1963 8-bit mode
    configure pins:
    hardware/io_SSD1963.h

    connected mcu -> tft
       ──────
    ──│      ├── PB2 ─── LCD_D0
    ──│      ├── PB3 ─── LCD_D1
    ──│      ├── PB4 ─── LCD_D2
    ──│      ├── PB5 ─── LCD_D3
    ──│      ├── PB6 ─── LCD_D4
    ──│      ├── PB7 ─── LCD_D5
    ──│      ├── PB8 ─── LCD_D6
    ──│      ├── PB9 ─── LCD_D7
    ──│      ├── PB10 ── LCD_RD
    ──│      ├── PB12 ── LCD_WR
    ──│      ├── PB13 ── LCD_RS
    ──│      ├── PB14 ── LCD_CS
    ──│      ├── PB15 ── LCD_RST
       ──────

    #define D0 2
    #define D1 3
    #define D2 4
    #define D3 5
    #define D4 6
    #define D5 7
    #define D6 8
    #define D7 9

    #define RD 10
    #define WR 12
    #define DC 13
    #define CS 14
    #define RST 15

    void tft_write_reg(uint8_t eightbit);
    void tft_write_data(uint8_t eightbit);
```

``` text
   https://lvgl.io/tools/fontconverter

   Added font arial bold

   Code page:  latin,  Cyrillic
   Range:     32-127, 1024-1120

   awesome font
   Range:
   61441,61448,61451,61452,61452,61453,61457,61459,61461,61465,
   61468,61473,61478,61479,61480,61502,61507,61512,61515,61516,
   61517,61521,61522,61523,61524,61543,61544,61550,61552,61553,
   61556,61559,61560,61561,61563,61587,61589,61636,61637,61639,
   61641,61664,61671,61674,61683,61724,61732,61787,61931,62016,
   62017,62018,62019,62020,62087,62099,62212,62189,62810,63426,
   63650
```
