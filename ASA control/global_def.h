#define ENABLE 1
#define DISABLE 0

#define BIT(bit) (0x01 << (bit))

//將data的第bit位元改為0
#define BIT_CLEAR(data, bit) ((data) &= ~(BIT(bit)))

//將data的第bit位元改為1
#define BIT_SET(data, bit) ((data) |= (BIT(bit)))

//將c蓋寫變數p的第m位元
#define BIT_PUT(c, p, m) (c ? BIT_SET(p, m) : BIT_CLEAR(p, m))

//檢查data的第bit位元是否為1
#define CheckBit(data, bit) ((data & (1 << bit)) == (1 << bit))