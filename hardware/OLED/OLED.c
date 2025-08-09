#include "OLED.h"

#define Soft_OLED_I2C   //ʹ������I2C   


uint8_t OLED_DisplayBuf[8][128];


#ifdef  Soft_OLED_I2C

#define  OLED_W_SCL(x)  ((x)?(DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_14)) : (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_14)) )
#define  OLED_W_SDA(x)  ((x)?(DL_GPIO_setPins(GPIOA,DL_GPIO_PIN_30)) : (DL_GPIO_clearPins(GPIOA,DL_GPIO_PIN_30)) )
#endif

#ifdef  Soft_OLED_SPI

#define OLED_W_D0(x)        ((x)?(DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_16)) : (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_16)) )
#define OLED_W_D1(x)        ((x)?(DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_15)) : (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_15)) )
#define OLED_W_RES(x)       ((x)?(DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_17)) : (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_17)) )
#define OLED_W_DC(x)        ((x)?(DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_1)) : (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_1)) )
#define OLED_W_CS(x)        ((x)?(DL_GPIO_setPins(GPIOA,DL_GPIO_PIN_29)) : (DL_GPIO_clearPins(GPIOA,DL_GPIO_PIN_29)) )

#endif

#ifdef  Hard_OLED_SPI

#define OLED_RES(x)        ((x)?(DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_17)) : (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_17)) )

#endif


void OLED_GPIO_Init(void)
{

#ifdef  Soft_OLED_I2C    

    OLED_W_SCL(1);
    OLED_W_SDA(1);
#endif    
    
#ifdef Soft_OLED_SPI

    
    /*������Ĭ�ϵ�ƽ*/
    OLED_W_D0(0);
    OLED_W_D1(1);
    OLED_W_RES(1);
    OLED_W_DC(1);
    OLED_W_CS(1);
#endif    

#ifdef Hard_OLED_SPI
    delay_ms(100);
    OLED_RES(0);
    delay_ms(20);
    OLED_RES(1);

#endif   
}


#ifdef  Soft_OLED_I2C


void OLED_I2C_Start(void)
{
    OLED_W_SDA(1);        //�ͷ�SDA��ȷ��SDAΪ�ߵ�ƽ
    OLED_W_SCL(1);        //�ͷ�SCL��ȷ��SCLΪ�ߵ�ƽ
    OLED_W_SDA(0);        //��SCL�ߵ�ƽ�ڼ䣬����SDA��������ʼ�ź�
    OLED_W_SCL(0);        //��ʼ���SCLҲ���ͣ���Ϊ��ռ�����ߣ�ҲΪ�˷�������ʱ���ƴ��
}


void OLED_I2C_Stop(void)
{
    OLED_W_SDA(0);        //����SDA��ȷ��SDAΪ�͵�ƽ
    OLED_W_SCL(1);        //�ͷ�SCL��ʹSCL���ָߵ�ƽ
    OLED_W_SDA(1);        //��SCL�ߵ�ƽ�ڼ䣬�ͷ�SDA��������ֹ�ź�
}
#endif

void OLED_I2C_SendByte(uint8_t Byte)
{
    uint8_t i;
#ifdef  Soft_OLED_I2C 
    /*ѭ��8�Σ��������η������ݵ�ÿһλ*/
    for (i = 0; i < 8; i++)
    {
        /*ʹ������ķ�ʽȡ��Byte��ָ��һλ���ݲ�д�뵽SDA��*/
        /*����!�������ǣ������з����ֵ��Ϊ1*/
        OLED_W_SDA(!!(Byte & (0x80 >> i)));
        OLED_W_SCL(1);    //�ͷ�SCL���ӻ���SCL�ߵ�ƽ�ڼ��ȡSDA
        OLED_W_SCL(0);    //����SCL��������ʼ������һλ����
    }
    
    OLED_W_SCL(1);        //�����һ��ʱ�ӣ�������Ӧ���ź�
    OLED_W_SCL(0);
#endif 
#ifdef Soft_OLED_SPI
    /*ѭ��8�Σ��������η������ݵ�ÿһλ*/
    for (i = 0; i < 8; i++)
    {
        /*ʹ������ķ�ʽȡ��Byte��ָ��һλ���ݲ�д�뵽D1��*/
        /*����!�������ǣ������з����ֵ��Ϊ1*/
        OLED_W_D1(!!(Byte & (0x80 >> i)));
        OLED_W_D0(1);    //����D0���ӻ���D0�����ض�ȡSDA
        OLED_W_D0(0);    //����D0��������ʼ������һλ����
    }
#endif
#ifdef Hard_OLED_SPI
    SPI_WriteByte(Byte);
#endif


}


void OLED_WriteCommand(uint8_t Command)
{
#ifdef  Soft_OLED_I2C 
    OLED_I2C_Start();                //I2C��ʼ
    OLED_I2C_SendByte(0x78);        //����OLED��I2C�ӻ���ַ
    OLED_I2C_SendByte(0x00);        //�����ֽڣ���0x00����ʾ����д����
    OLED_I2C_SendByte(Command);        //д��ָ��������
    OLED_I2C_Stop();                //I2C��ֹ
#endif   
#ifdef  Hard_OLED_I2C   
    i2c0_write_n_byte(0x3C, 0x00, &Command, 1);
#endif      
#ifdef Soft_OLED_SPI
    OLED_W_CS(0);                    //����CS����ʼͨ��
    OLED_W_DC(0);                    //����DC����ʾ������������
    OLED_I2C_SendByte(Command);        //д��ָ������
    OLED_W_CS(1);                    //����CS������ͨ��
#endif 
    
#ifdef Hard_OLED_SPI
    SPI_Send_cmd(Command);
#endif    
    
    
}


void OLED_WriteData(uint8_t *Data, uint8_t Count)
{
    uint8_t i;
#ifdef  Soft_OLED_I2C 
    OLED_I2C_Start();                //I2C��ʼ
    OLED_I2C_SendByte(0x78);        //����OLED��I2C�ӻ���ַ
    OLED_I2C_SendByte(0x40);        //�����ֽڣ���0x40����ʾ����д����
    /*ѭ��Count�Σ���������������д��*/
    for (i = 0; i < Count; i ++)
    {
        OLED_I2C_SendByte(Data[i]);    //���η���Data��ÿһ������
    }
    OLED_I2C_Stop();                //I2C��ֹ
#endif   
#ifdef  Hard_OLED_I2C   
   i2c0_write_n_byte(0x3C, 0x40, Data, Count);
#endif      
#ifdef Soft_OLED_SPI
    OLED_W_CS(0);                    //����CS����ʼͨ��
    OLED_W_DC(1);                    //����DC����ʾ������������
    /*ѭ��Count�Σ���������������д��*/
    for (i = 0; i < Count; i ++)
    {
        OLED_I2C_SendByte(Data[i]);    //���η���Data��ÿһ������
    }
    OLED_W_CS(1);                    //����CS������ͨ��
#endif  

#ifdef Hard_OLED_SPI
    for (i = 0; i < Count; i ++)
    {
        SPI_WriteByte(Data[i]);    //���η���Data��ÿһ������
    }
#endif    

}



void OLED_Init(void)
{
    OLED_GPIO_Init();            //�ȵ��õײ�Ķ˿ڳ�ʼ��
    
    /*д��һϵ�е������OLED���г�ʼ������*/
    OLED_WriteCommand(0xAE);    //������ʾ����/�رգ�0xAE�رգ�0xAF����
    
    OLED_WriteCommand(0xD5);    //������ʾʱ�ӷ�Ƶ��/����Ƶ��
    OLED_WriteCommand(0x80);    //0x00~0xFF
    
    OLED_WriteCommand(0xA8);    //���ö�·������
    OLED_WriteCommand(0x3F);    //0x0E~0x3F
    
    OLED_WriteCommand(0xD3);    //������ʾƫ��
    OLED_WriteCommand(0x00);    //0x00~0x7F
    
    OLED_WriteCommand(0x40);    //������ʾ��ʼ�У�0x40~0x7F
    
    OLED_WriteCommand(0xA1);    //�������ҷ���0xA1������0xA0���ҷ���
    
    OLED_WriteCommand(0xC8);    //�������·���0xC8������0xC0���·���

    OLED_WriteCommand(0xDA);    //����COM����Ӳ������
    OLED_WriteCommand(0x12);
    
    OLED_WriteCommand(0x81);    //���öԱȶ�
    OLED_WriteCommand(0xCF);    //0x00~0xFF

    OLED_WriteCommand(0xD9);    //����Ԥ�������
    OLED_WriteCommand(0xF1);

    OLED_WriteCommand(0xDB);    //����VCOMHȡ��ѡ�񼶱�
    OLED_WriteCommand(0x30);

    OLED_WriteCommand(0xA4);    //����������ʾ��/�ر�

    OLED_WriteCommand(0xA6);    //��������/��ɫ��ʾ��0xA6������0xA7��ɫ

    OLED_WriteCommand(0x8D);    //���ó���
    OLED_WriteCommand(0x14);

    OLED_WriteCommand(0xAF);    //������ʾ
}


void OLED_SetCursor(uint8_t Page, uint8_t X)
{

    OLED_WriteCommand(0xB0 | Page);                    //����ҳλ��
    OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));    //����Xλ�ø�4λ
    OLED_WriteCommand(0x00 | (X & 0x0F));            //����Xλ�õ�4λ
}


uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;    //���Ĭ��Ϊ1
    while (Y --)            //�۳�Y��
    {
        Result *= X;        //ÿ�ΰ�X�۳˵������
    }
    return Result;
}


uint8_t OLED_pnpoly(uint8_t nvert, int16_t *vertx, int16_t *verty, int16_t testx, int16_t testy)
{
    int16_t i, j, c = 0;
    
    /*���㷨��W. Randolph Franklin���*/
    /*�ο����ӣ�https://wrfranklin.org/Research/Short_Notes/pnpoly.html*/
    for (i = 0, j = nvert - 1; i < nvert; j = i++)
    {
        if (((verty[i] > testy) != (verty[j] > testy)) &&
            (testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
        {
            c = !c;
        }
    }
    return c;
}


uint8_t OLED_IsInAngle(int16_t X, int16_t Y, int16_t StartAngle, int16_t EndAngle)
{
    int16_t PointAngle;
    PointAngle = atan2(Y, X) / 3.14 * 180;    //����ָ����Ļ��ȣ���ת��Ϊ�Ƕȱ�ʾ
    if (StartAngle < EndAngle)    //��ʼ�Ƕ�С����ֹ�Ƕȵ����
    {
        /*���ָ���Ƕ�����ʼ��ֹ�Ƕ�֮�䣬���ж�ָ������ָ���Ƕ�*/
        if (PointAngle >= StartAngle && PointAngle <= EndAngle)
        {
            return 1;
        }
    }
    else            //��ʼ�Ƕȴ�������ֹ�Ƕȵ����
    {
        /*���ָ���Ƕȴ�����ʼ�ǶȻ���С����ֹ�Ƕȣ����ж�ָ������ָ���Ƕ�*/
        if (PointAngle >= StartAngle || PointAngle <= EndAngle)
        {
            return 1;
        }
    }
    return 0;        //�������������������ж��ж�ָ���㲻��ָ���Ƕ�
}


void OLED_Update(void)
{
    uint8_t j;
    /*����ÿһҳ*/
    for (j = 0; j < 8; j ++)
    {
        /*���ù��λ��Ϊÿһҳ�ĵ�һ��*/
        OLED_SetCursor(j, 0);
        /*����д��128�����ݣ����Դ����������д�뵽OLEDӲ��*/
        OLED_WriteData(OLED_DisplayBuf[j], 128);
    }
}


void OLED_UpdateArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height)
{
    uint8_t j;
    
    /*������飬��ָ֤�����򲻻ᳬ����Ļ��Χ*/
    if (X > 127) {return;}
    if (Y > 63) {return;}
    if (X + Width > 128) {Width = 128 - X;}
    if (Y + Height > 64) {Height = 64 - Y;}
    
    /*����ָ�������漰�����ҳ*/
    /*(Y + Height - 1) / 8 + 1��Ŀ����(Y + Height) / 8������ȡ��*/
    for (j = Y / 8; j < (Y + Height - 1) / 8 + 1; j ++)
    {
        /*���ù��λ��Ϊ���ҳ��ָ����*/
        OLED_SetCursor(j, X);
        /*����д��Width�����ݣ����Դ����������д�뵽OLEDӲ��*/
        OLED_WriteData(&OLED_DisplayBuf[j][X], Width);
    }
}


void OLED_Clear(void)
{
    uint8_t i, j;
    for (j = 0; j < 8; j ++)                //����8ҳ
    {
        for (i = 0; i < 128; i ++)            //����128��
        {
            OLED_DisplayBuf[j][i] = 0x00;    //���Դ���������ȫ������
        }
    }
}


void OLED_ClearArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height)
{
    uint8_t i, j;
    
    /*������飬��ָ֤�����򲻻ᳬ����Ļ��Χ*/
    if (X > 127) {return;}
    if (Y > 63) {return;}
    if (X + Width > 128) {Width = 128 - X;}
    if (Y + Height > 64) {Height = 64 - Y;}
    
    for (j = Y; j < Y + Height; j ++)        //����ָ��ҳ
    {
        for (i = X; i < X + Width; i ++)    //����ָ����
        {
            OLED_DisplayBuf[j / 8][i] &= ~(0x01 << (j % 8));    //���Դ�����ָ����������
        }
    }
}


void OLED_Reverse(void)
{
    uint8_t i, j;
    for (j = 0; j < 8; j ++)                //����8ҳ
    {
        for (i = 0; i < 128; i ++)            //����128��
        {
            OLED_DisplayBuf[j][i] ^= 0xFF;    //���Դ���������ȫ��ȡ��
        }
    }
}
    

void OLED_ReverseArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height)
{
    uint8_t i, j;
    
    /*������飬��ָ֤�����򲻻ᳬ����Ļ��Χ*/
    if (X > 127) {return;}
    if (Y > 63) {return;}
    if (X + Width > 128) {Width = 128 - X;}
    if (Y + Height > 64) {Height = 64 - Y;}
    
    for (j = Y; j < Y + Height; j ++)        //����ָ��ҳ
    {
        for (i = X; i < X + Width; i ++)    //����ָ����
        {
            OLED_DisplayBuf[j / 8][i] ^= 0x01 << (j % 8);    //���Դ�����ָ������ȡ��
        }
    }
}


void OLED_ShowChar(uint8_t X, uint8_t Y, char Char, uint8_t FontSize)
{
    if (FontSize == OLED_8X16)        //����Ϊ��8���أ���16����
    {
        /*��ASCII��ģ��OLED_F8x16��ָ��������8*16��ͼ���ʽ��ʾ*/
        OLED_ShowImage(X, Y, 8, 16, OLED_F8x16[Char - ' ']);
    }
    else if(FontSize == OLED_6X8)    //����Ϊ��6���أ���8����
    {
        /*��ASCII��ģ��OLED_F6x8��ָ��������6*8��ͼ���ʽ��ʾ*/
        OLED_ShowImage(X, Y, 6, 8, OLED_F6x8[Char - ' ']);
    }
}


void OLED_ShowString(uint8_t X, uint8_t Y, char *String, uint8_t FontSize)
{
    uint8_t i;
    for (i = 0; String[i] != '\0'; i++)        //�����ַ�����ÿ���ַ�
    {
        /*����OLED_ShowChar������������ʾÿ���ַ�*/
        OLED_ShowChar(X + i * FontSize, Y, String[i], FontSize);
    }
}


void OLED_ShowNum(uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
    uint8_t i;
    for (i = 0; i < Length; i++)        //�������ֵ�ÿһλ                            
    {

        OLED_ShowChar(X + i * FontSize, Y, Number / OLED_Pow(10, Length - i - 1) % 10 + '0', FontSize);
    }
}


void OLED_ShowSignedNum(uint8_t X, uint8_t Y, int32_t Number, uint8_t Length, uint8_t FontSize)
{
    uint8_t i;
    uint32_t Number1;
    
    if (Number >= 0)                        //���ִ��ڵ���0
    {
        OLED_ShowChar(X, Y, '+', FontSize);    //��ʾ+��
        Number1 = Number;                    //Number1ֱ�ӵ���Number
    }
    else                                    //����С��0
    {
        OLED_ShowChar(X, Y, '-', FontSize);    //��ʾ-��
        Number1 = -Number;                    //Number1����Numberȡ��
    }
    
    for (i = 0; i < Length; i++)            //�������ֵ�ÿһλ                                
    {

        OLED_ShowChar(X + (i + 1) * FontSize, Y, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0', FontSize);
    }
}


void OLED_ShowHexNum(uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
    uint8_t i, SingleNumber;
    for (i = 0; i < Length; i++)        //�������ֵ�ÿһλ
    {
        /*��ʮ��������ȡ���ֵ�ÿһλ*/
        SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
        
        if (SingleNumber < 10)            //��������С��10
        {
            /*����OLED_ShowChar��������ʾ������*/
            /*+ '0' �ɽ�����ת��Ϊ�ַ���ʽ*/
            OLED_ShowChar(X + i * FontSize, Y, SingleNumber + '0', FontSize);
        }
        else                            //�������ִ���10
        {
            /*����OLED_ShowChar��������ʾ������*/
            /*+ 'A' �ɽ�����ת��Ϊ��A��ʼ��ʮ�������ַ�*/
            OLED_ShowChar(X + i * FontSize, Y, SingleNumber - 10 + 'A', FontSize);
        }
    }
}


void OLED_ShowBinNum(uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
    uint8_t i;
    for (i = 0; i < Length; i++)        //�������ֵ�ÿһλ    
    {
        /*����OLED_ShowChar������������ʾÿ������*/
        /*Number / OLED_Pow(2, Length - i - 1) % 2 ���Զ�������ȡ���ֵ�ÿһλ*/
        /*+ '0' �ɽ�����ת��Ϊ�ַ���ʽ*/
        OLED_ShowChar(X + i * FontSize, Y, Number / OLED_Pow(2, Length - i - 1) % 2 + '0', FontSize);
    }
}


void OLED_ShowFloatNum(uint8_t X, uint8_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize)
{
    uint32_t Temp;
    
    if (Number >= 0)                        //���ִ��ڵ���0
    {
        OLED_ShowChar(X, Y, '+', FontSize);    //��ʾ+��
    }
    else                                    //����С��0
    {
        OLED_ShowChar(X, Y, '-', FontSize);    //��ʾ-��
        Number = -Number;                    //Numberȡ��
    }
    
    /*��ʾ��������*/
    OLED_ShowNum(X + FontSize, Y, Number, IntLength, FontSize);
    
    /*��ʾС����*/
    OLED_ShowChar(X + (IntLength + 1) * FontSize, Y, '.', FontSize);
    
    /*��Number���������ּ�������ֹ֮��С�����ֳ˵�����ʱ����������ɴ���*/
    Number -= (uint32_t)Number;
    
    /*��С�����ֳ˵��������֣�����ʾ*/
    Temp = OLED_Pow(10, FraLength);
    OLED_ShowNum(X + (IntLength + 2) * FontSize, Y, ((uint32_t)(Number * Temp)) % Temp, FraLength, FontSize);
}


void OLED_ShowChinese(uint8_t X, uint8_t Y, char *Chinese)
{
    uint8_t pChinese = 0;
    uint8_t pIndex;
    uint8_t i;
    char SingleChinese[OLED_CHN_CHAR_WIDTH + 1] = {0};
    
    for (i = 0; Chinese[i] != '\0'; i ++)        //�������ִ�
    {
        SingleChinese[pChinese] = Chinese[i];    //��ȡ���ִ����ݵ�������������
        pChinese ++;                            //�ƴ�����
        
        /*����ȡ��������OLED_CHN_CHAR_WIDTHʱ����������ȡ����һ�������ĺ���*/
        if (pChinese >= OLED_CHN_CHAR_WIDTH)
        {
            pChinese = 0;        //�ƴι���
            
            /*��������������ģ�⣬Ѱ��ƥ��ĺ���*/
            /*����ҵ����һ�����֣�����Ϊ���ַ����������ʾ����δ����ģ�ⶨ�壬ֹͣѰ��*/
            for (pIndex = 0; strcmp(OLED_CF16x16[pIndex].Index, "") != 0; pIndex ++)
            {
                /*�ҵ�ƥ��ĺ���*/
                if (strcmp(OLED_CF16x16[pIndex].Index, SingleChinese) == 0)
                {
                    break;        //����ѭ������ʱpIndex��ֵΪָ�����ֵ�����
                }
            }
            
            /*��������ģ��OLED_CF16x16��ָ��������16*16��ͼ���ʽ��ʾ*/
            OLED_ShowImage(X + ((i + 1) / OLED_CHN_CHAR_WIDTH - 1) * 16, Y, 16, 16, OLED_CF16x16[pIndex].Data);
        }
    }
}


void OLED_ShowImage(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image)
{
    uint8_t i, j;
    
    /*������飬��ָ֤��ͼ�񲻻ᳬ����Ļ��Χ*/
    if (X > 127) {return;}
    if (Y > 63) {return;}
    
    /*��ͼ�������������*/
    OLED_ClearArea(X, Y, Width, Height);
    
    /*����ָ��ͼ���漰�����ҳ*/
    /*(Height - 1) / 8 + 1��Ŀ����Height / 8������ȡ��*/
    for (j = 0; j < (Height - 1) / 8 + 1; j ++)
    {
        /*����ָ��ͼ���漰�������*/
        for (i = 0; i < Width; i ++)
        {
            /*�����߽磬��������ʾ*/
            if (X + i > 127) {break;}
            if (Y / 8 + j > 7) {return;}
            
            /*��ʾͼ���ڵ�ǰҳ������*/
            OLED_DisplayBuf[Y / 8 + j][X + i] |= Image[j * Width + i] << (Y % 8);
            
            /*�����߽磬��������ʾ*/
            /*ʹ��continue��Ŀ���ǣ���һҳ�����߽�ʱ����һҳ�ĺ������ݻ���Ҫ������ʾ*/
            if (Y / 8 + j + 1 > 7) {continue;}
            
            /*��ʾͼ������һҳ������*/
            OLED_DisplayBuf[Y / 8 + j + 1][X + i] |= Image[j * Width + i] >> (8 - Y % 8);
        }
    }
}


void OLED_Printf(uint8_t X, uint8_t Y, uint8_t FontSize, char *format, ...)
{
    char String[30];                        //�����ַ�����
    va_list arg;                            //����ɱ�����б��������͵ı���arg
    va_start(arg, format);                    //��format��ʼ�����ղ����б���arg����
    vsprintf(String, format, arg);            //ʹ��vsprintf��ӡ��ʽ���ַ����Ͳ����б����ַ�������
    va_end(arg);                            //��������arg
    OLED_ShowString(X, Y, String, FontSize);//OLED��ʾ�ַ����飨�ַ�����
}


void OLED_DrawPoint(uint8_t X, uint8_t Y)
{
    /*������飬��ָ֤��λ�ò��ᳬ����Ļ��Χ*/
    if (X > 127) {return;}
    if (Y > 63) {return;}
    
    /*���Դ�����ָ��λ�õ�һ��Bit������1*/
    OLED_DisplayBuf[Y / 8][X] |= 0x01 << (Y % 8);
}


uint8_t OLED_GetPoint(uint8_t X, uint8_t Y)
{
    /*������飬��ָ֤��λ�ò��ᳬ����Ļ��Χ*/
    if (X > 127) {return 0;}
    if (Y > 63) {return 0;}
    
    /*�ж�ָ��λ�õ�����*/
    if (OLED_DisplayBuf[Y / 8][X] & 0x01 << (Y % 8))
    {
        return 1;    //Ϊ1������1
    }
    
    return 0;        //���򣬷���0
}


void OLED_DrawLine(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1)
{
    int16_t x, y, dx, dy, d, incrE, incrNE, temp;
    int16_t x0 = X0, y0 = Y0, x1 = X1, y1 = Y1;
    uint8_t yflag = 0, xyflag = 0;
    
    if (y0 == y1)        //���ߵ�������
    {
        /*0�ŵ�X�������1�ŵ�X���꣬�򽻻�����X����*/
        if (x0 > x1) {temp = x0; x0 = x1; x1 = temp;}
        
        /*����X����*/
        for (x = x0; x <= x1; x ++)
        {
            OLED_DrawPoint(x, y0);    //���λ���
        }
    }
    else if (x0 == x1)    //���ߵ�������
    {
        /*0�ŵ�Y�������1�ŵ�Y���꣬�򽻻�����Y����*/
        if (y0 > y1) {temp = y0; y0 = y1; y1 = temp;}
        
        /*����Y����*/
        for (y = y0; y <= y1; y ++)
        {
            OLED_DrawPoint(x0, y);    //���λ���
        }
    }
    else                //б��
    {
      
        
        if (x0 > x1)    //0�ŵ�X�������1�ŵ�X����
        {
            /*������������*/
            /*������Ӱ�컭�ߣ����ǻ��߷����ɵ�һ���������������ޱ�Ϊ��һ��������*/
            temp = x0; x0 = x1; x1 = temp;
            temp = y0; y0 = y1; y1 = temp;
        }
        
        if (y0 > y1)    //0�ŵ�Y�������1�ŵ�Y����
        {
            /*��Y����ȡ��*/
            /*ȡ����Ӱ�컭�ߣ����ǻ��߷����ɵ�һ�������ޱ�Ϊ��һ����*/
            y0 = -y0;
            y1 = -y1;
            
            /*�ñ�־λyflag����ס��ǰ�任���ں���ʵ�ʻ���ʱ���ٽ����껻����*/
            yflag = 1;
        }
        
        if (y1 - y0 > x1 - x0)    //����б�ʴ���1
        {
            /*��X������Y���껥��*/
            /*������Ӱ�컭�ߣ����ǻ��߷����ɵ�һ����0~90�ȷ�Χ��Ϊ��һ����0~45�ȷ�Χ*/
            temp = x0; x0 = y0; y0 = temp;
            temp = x1; x1 = y1; y1 = temp;
            
            /*�ñ�־λxyflag����ס��ǰ�任���ں���ʵ�ʻ���ʱ���ٽ����껻����*/
            xyflag = 1;
        }
        
        /*����ΪBresenham�㷨��ֱ��*/
        /*�㷨Ҫ�󣬻��߷������Ϊ��һ����0~45�ȷ�Χ*/
        dx = x1 - x0;
        dy = y1 - y0;
        incrE = 2 * dy;
        incrNE = 2 * (dy - dx);
        d = 2 * dy - dx;
        x = x0;
        y = y0;
        
        /*����ʼ�㣬ͬʱ�жϱ�־λ�������껻����*/
        if (yflag && xyflag){OLED_DrawPoint(y, -x);}
        else if (yflag)        {OLED_DrawPoint(x, -y);}
        else if (xyflag)    {OLED_DrawPoint(y, x);}
        else                {OLED_DrawPoint(x, y);}
        
        while (x < x1)        //����X���ÿ����
        {
            x ++;
            if (d < 0)        //��һ�����ڵ�ǰ�㶫��
            {
                d += incrE;
            }
            else            //��һ�����ڵ�ǰ�㶫����
            {
                y ++;
                d += incrNE;
            }
            
            /*��ÿһ���㣬ͬʱ�жϱ�־λ�������껻����*/
            if (yflag && xyflag){OLED_DrawPoint(y, -x);}
            else if (yflag)        {OLED_DrawPoint(x, -y);}
            else if (xyflag)    {OLED_DrawPoint(y, x);}
            else                {OLED_DrawPoint(x, y);}
        }    
    }
}


void OLED_DrawRectangle(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, uint8_t IsFilled)
{
    uint8_t i, j;
    if (!IsFilled)        //ָ�����β����
    {
        /*��������X���꣬����������������*/
        for (i = X; i < X + Width; i ++)
        {
            OLED_DrawPoint(i, Y);
            OLED_DrawPoint(i, Y + Height - 1);
        }
        /*��������Y���꣬����������������*/
        for (i = Y; i < Y + Height; i ++)
        {
            OLED_DrawPoint(X, i);
            OLED_DrawPoint(X + Width - 1, i);
        }
    }
    else                //ָ���������
    {
        /*����X����*/
        for (i = X; i < X + Width; i ++)
        {
            /*����Y����*/
            for (j = Y; j < Y + Height; j ++)
            {
                /*��ָ�����򻭵㣬���������*/
                OLED_DrawPoint(i, j);
            }
        }
    }
}


void OLED_DrawTriangle(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, uint8_t IsFilled)
{
    uint8_t minx = X0, miny = Y0, maxx = X0, maxy = Y0;
    uint8_t i, j;
    int16_t vx[] = {X0, X1, X2};
    int16_t vy[] = {Y0, Y1, Y2};
    
    if (!IsFilled)            //ָ�������β����
    {
        /*���û��ߺ���������������ֱ������*/
        OLED_DrawLine(X0, Y0, X1, Y1);
        OLED_DrawLine(X0, Y0, X2, Y2);
        OLED_DrawLine(X1, Y1, X2, Y2);
    }
    else                    //ָ�����������
    {
        /*�ҵ���������С��X��Y����*/
        if (X1 < minx) {minx = X1;}
        if (X2 < minx) {minx = X2;}
        if (Y1 < miny) {miny = Y1;}
        if (Y2 < miny) {miny = Y2;}
        
        /*�ҵ�����������X��Y����*/
        if (X1 > maxx) {maxx = X1;}
        if (X2 > maxx) {maxx = X2;}
        if (Y1 > maxy) {maxy = Y1;}
        if (Y2 > maxy) {maxy = Y2;}
        
    
        for (i = minx; i <= maxx; i ++)
        {
            /*����Y����*/    
            for (j = miny; j <= maxy; j ++)
            {
                /*����OLED_pnpoly���ж�ָ�����Ƿ���ָ��������֮��*/
                /*����ڣ��򻭵㣬������ڣ���������*/
                if (OLED_pnpoly(3, vx, vy, i, j)) {OLED_DrawPoint(i, j);}
            }
        }
    }
}


void OLED_DrawCircle(uint8_t X, uint8_t Y, uint8_t Radius, uint8_t IsFilled)
{
    int16_t x, y, d, j;
    
    d = 1 - Radius;
    x = 0;
    y = Radius;
    
    /*��ÿ���˷�֮һԲ������ʼ��*/
    OLED_DrawPoint(X + x, Y + y);
    OLED_DrawPoint(X - x, Y - y);
    OLED_DrawPoint(X + y, Y + x);
    OLED_DrawPoint(X - y, Y - x);
    
    if (IsFilled)        //ָ��Բ���
    {
        /*������ʼ��Y����*/
        for (j = -y; j < y; j ++)
        {
            /*��ָ�����򻭵㣬��䲿��Բ*/
            OLED_DrawPoint(X, Y + j);
        }
    }
    
    while (x < y)        //����X���ÿ����
    {
        x ++;
        if (d < 0)        //��һ�����ڵ�ǰ�㶫��
        {
            d += 2 * x + 1;
        }
        else            //��һ�����ڵ�ǰ�㶫�Ϸ�
        {
            y --;
            d += 2 * (x - y) + 1;
        }
        
        /*��ÿ���˷�֮һԲ���ĵ�*/
        OLED_DrawPoint(X + x, Y + y);
        OLED_DrawPoint(X + y, Y + x);
        OLED_DrawPoint(X - x, Y - y);
        OLED_DrawPoint(X - y, Y - x);
        OLED_DrawPoint(X + x, Y - y);
        OLED_DrawPoint(X + y, Y - x);
        OLED_DrawPoint(X - x, Y + y);
        OLED_DrawPoint(X - y, Y + x);
        
        if (IsFilled)    //ָ��Բ���
        {
            /*�����м䲿��*/
            for (j = -y; j < y; j ++)
            {
                /*��ָ�����򻭵㣬��䲿��Բ*/
                OLED_DrawPoint(X + x, Y + j);
                OLED_DrawPoint(X - x, Y + j);
            }
            
            /*�������ಿ��*/
            for (j = -x; j < x; j ++)
            {
                /*��ָ�����򻭵㣬��䲿��Բ*/
                OLED_DrawPoint(X - y, Y + j);
                OLED_DrawPoint(X + y, Y + j);
            }
        }
    }
}


void OLED_DrawEllipse(uint8_t X, uint8_t Y, uint8_t A, uint8_t B, uint8_t IsFilled)
{
    int16_t x, y, j;
    int16_t a = A, b = B;
    float d1, d2;
    
    /*ʹ��Bresenham�㷨����Բ�����Ա��ⲿ�ֺ�ʱ�ĸ������㣬Ч�ʸ���*/
    /*�ο����ӣ�https://blog.csdn.net/myf_666/article/details/128167392*/
    
    x = 0;
    y = b;
    d1 = b * b + a * a * (-b + 0.5);
    
    if (IsFilled)    //ָ����Բ���
    {
        /*������ʼ��Y����*/
        for (j = -y; j < y; j ++)
        {
            /*��ָ�����򻭵㣬��䲿����Բ*/
            OLED_DrawPoint(X, Y + j);
            OLED_DrawPoint(X, Y + j);
        }
    }
    
    /*����Բ������ʼ��*/
    OLED_DrawPoint(X + x, Y + y);
    OLED_DrawPoint(X - x, Y - y);
    OLED_DrawPoint(X - x, Y + y);
    OLED_DrawPoint(X + x, Y - y);
    
    /*����Բ�м䲿��*/
    while (b * b * (x + 1) < a * a * (y - 0.5))
    {
        if (d1 <= 0)        //��һ�����ڵ�ǰ�㶫��
        {
            d1 += b * b * (2 * x + 3);
        }
        else                //��һ�����ڵ�ǰ�㶫�Ϸ�
        {
            d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
            y --;
        }
        x ++;
        
        if (IsFilled)    //ָ����Բ���
        {
            /*�����м䲿��*/
            for (j = -y; j < y; j ++)
            {
                /*��ָ�����򻭵㣬��䲿����Բ*/
                OLED_DrawPoint(X + x, Y + j);
                OLED_DrawPoint(X - x, Y + j);
            }
        }
        
        /*����Բ�м䲿��Բ��*/
        OLED_DrawPoint(X + x, Y + y);
        OLED_DrawPoint(X - x, Y - y);
        OLED_DrawPoint(X - x, Y + y);
        OLED_DrawPoint(X + x, Y - y);
    }
    
    /*����Բ���ಿ��*/
    d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
    
    while (y > 0)
    {
        if (d2 <= 0)        //��һ�����ڵ�ǰ�㶫��
        {
            d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
            x ++;
            
        }
        else                //��һ�����ڵ�ǰ�㶫�Ϸ�
        {
            d2 += a * a * (-2 * y + 3);
        }
        y --;
        
        if (IsFilled)    //ָ����Բ���
        {
            /*�������ಿ��*/
            for (j = -y; j < y; j ++)
            {
                /*��ָ�����򻭵㣬��䲿����Բ*/
                OLED_DrawPoint(X + x, Y + j);
                OLED_DrawPoint(X - x, Y + j);
            }
        }
        
        /*����Բ���ಿ��Բ��*/
        OLED_DrawPoint(X + x, Y + y);
        OLED_DrawPoint(X - x, Y - y);
        OLED_DrawPoint(X - x, Y + y);
        OLED_DrawPoint(X + x, Y - y);
    }
}


void OLED_DrawArc(uint8_t X, uint8_t Y, uint8_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled)
{
    int16_t x, y, d, j;
    
    /*�˺�������Bresenham�㷨��Բ�ķ���*/
    
    d = 1 - Radius;
    x = 0;
    y = Radius;
    
    /*�ڻ�Բ��ÿ����ʱ���ж�ָ�����Ƿ���ָ���Ƕ��ڣ��ڣ��򻭵㣬���ڣ���������*/
    if (OLED_IsInAngle(x, y, StartAngle, EndAngle))    {OLED_DrawPoint(X + x, Y + y);}
    if (OLED_IsInAngle(-x, -y, StartAngle, EndAngle)) {OLED_DrawPoint(X - x, Y - y);}
    if (OLED_IsInAngle(y, x, StartAngle, EndAngle)) {OLED_DrawPoint(X + y, Y + x);}
    if (OLED_IsInAngle(-y, -x, StartAngle, EndAngle)) {OLED_DrawPoint(X - y, Y - x);}
    
    if (IsFilled)    //ָ��Բ�����
    {
        /*������ʼ��Y����*/
        for (j = -y; j < y; j ++)
        {
            /*�����Բ��ÿ����ʱ���ж�ָ�����Ƿ���ָ���Ƕ��ڣ��ڣ��򻭵㣬���ڣ���������*/
            if (OLED_IsInAngle(0, j, StartAngle, EndAngle)) {OLED_DrawPoint(X, Y + j);}
        }
    }
    
    while (x < y)        //����X���ÿ����
    {
        x ++;
        if (d < 0)        //��һ�����ڵ�ǰ�㶫��
        {
            d += 2 * x + 1;
        }
        else            //��һ�����ڵ�ǰ�㶫�Ϸ�
        {
            y --;
            d += 2 * (x - y) + 1;
        }
        
        /*�ڻ�Բ��ÿ����ʱ���ж�ָ�����Ƿ���ָ���Ƕ��ڣ��ڣ��򻭵㣬���ڣ���������*/
        if (OLED_IsInAngle(x, y, StartAngle, EndAngle)) {OLED_DrawPoint(X + x, Y + y);}
        if (OLED_IsInAngle(y, x, StartAngle, EndAngle)) {OLED_DrawPoint(X + y, Y + x);}
        if (OLED_IsInAngle(-x, -y, StartAngle, EndAngle)) {OLED_DrawPoint(X - x, Y - y);}
        if (OLED_IsInAngle(-y, -x, StartAngle, EndAngle)) {OLED_DrawPoint(X - y, Y - x);}
        if (OLED_IsInAngle(x, -y, StartAngle, EndAngle)) {OLED_DrawPoint(X + x, Y - y);}
        if (OLED_IsInAngle(y, -x, StartAngle, EndAngle)) {OLED_DrawPoint(X + y, Y - x);}
        if (OLED_IsInAngle(-x, y, StartAngle, EndAngle)) {OLED_DrawPoint(X - x, Y + y);}
        if (OLED_IsInAngle(-y, x, StartAngle, EndAngle)) {OLED_DrawPoint(X - y, Y + x);}
        
        if (IsFilled)    //ָ��Բ�����
        {
            /*�����м䲿��*/
            for (j = -y; j < y; j ++)
            {
                /*�����Բ��ÿ����ʱ���ж�ָ�����Ƿ���ָ���Ƕ��ڣ��ڣ��򻭵㣬���ڣ���������*/
                if (OLED_IsInAngle(x, j, StartAngle, EndAngle)) {OLED_DrawPoint(X + x, Y + j);}
                if (OLED_IsInAngle(-x, j, StartAngle, EndAngle)) {OLED_DrawPoint(X - x, Y + j);}
            }
            
            /*�������ಿ��*/
            for (j = -x; j < x; j ++)
            {
                /*�����Բ��ÿ����ʱ���ж�ָ�����Ƿ���ָ���Ƕ��ڣ��ڣ��򻭵㣬���ڣ���������*/
                if (OLED_IsInAngle(-y, j, StartAngle, EndAngle)) {OLED_DrawPoint(X - y, Y + j);}
                if (OLED_IsInAngle(y, j, StartAngle, EndAngle)) {OLED_DrawPoint(X + y, Y + j);}
            }
        }
    }
}

