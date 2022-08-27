/*

    Wire.beginTransmission(I2C_BMP_208);
    Wire.write(0xF4);
    Wire.write(tmp_to_send);

    Wire.write(0xF5);
    Wire.write(tmp_to_send2);
    Wire.endTransmission(true);
*/
#include <Wire.h>
#define SDA_PIN D2
#define SCL_PIN D1

const int16_t I2C_MASTER = 0x42;
const int16_t I2C_L3G4200D = 0x69; //I2C address L3G4200D

#define CTRL_REG1_address 0x20
#define CTRL_REG2_address 0x21
#define CTRL_REG3_address 0x22
#define CTRL_REG4_address 0x23
#define CTRL_REG5_address 0x24
//int CTRL_REG6_address = 0x;
#define Reference_address 0x25
#define INT1_THS_XH_address 0x32
#define INT1_THS_XL_address 0x33
#define INT1_THS_YH_address 0x34
#define INT1_THS_YL_address 0x35
#define INT1_THS_ZH_address 0x36
#define INT1_THS_ZL_address 0x37
#define INT1_DUR_address 0x38
#define INT1_CFG_address 0x30
#define FIFO_CTRL_REG_address 0x2E
#define FIFO_SRC_REG_address 0x2F
#define OUT_TEMP_address 0x26

int PD = 1;         //PD 0 Power down/ 1 Sleep or Normal mode
int Zen = 1;        //0 Sleep / - Power down or Normal mode
int Yen = 1;        //0 Sleep / - Power down or Normal mode
int Xen = 1;        //0 Sleep / - Power down or Normal mode
int DR = B11;       //table 3 Data rate configuration
int BW = B11;       //table 3 Data rate configuration
int BLE = 0;        //Little Endian low in low, big in big
int BDU = 1;        //Using the block data update (BDU) feature
int FS = B11;       //FS00 = 250 dps, FS01 = 500 dps? not reliable information - FS10 or 11 = 2000 dps
int ST = B00;       //maybe it's self test
int SIM = 0;        //SPI read in 3-wires mode (3-wires mode is entered by setting to 1 bit SIM (SPI serial interface mode selection))
int BOOT = 0;       //???
int FIFO_EN = 0;    //FIFO enable
int REF = B00000000;//Delta to Reference mode

int FM = B011;      //table 29
int WTM = B1111;    //table 29

int WTM_SRC = 0;
int OVRN  = 0;
int EMPTY = 0;
int FSS = B00000;


//Interrupt generation
int I1_Int1 = 0;    //Interrupt enable on INT1 pin. Default value 0. (0: Disable; 1: Enable)
int I1_Boot = 0;    //Boot status available on INT1. Default value 0. (0: Disable; 1: Enable)
int H_Lactive = 0;  //Interrupt active configuration on INT1. Default value 0. (0: High; 1:Low)
int PP_OD = 0;      //Push-Pull / Open drain. Default value: 0. (0: Push-Pull; 1: Open drain)
int I2_DRDY = 1;    //Date Ready on DRDY/INT2. Default value 0. (0: Disable; 1: Enable)
int I2_WTM = 0;     //FIFO Watermark interrupt on DRDY/INT2. Default value: 0. (0: Disable; 1: Enable)
int I2_ORun = 0;    //FIFO Overrun interrupt on DRDY/INT2 Default value: 0. (0: Disable; 1: Enable)
int I2_Empty = 0;   //FIFO Empty interrupt on DRDY/INT2. Default value: 0. (0: Disable; 1: Enable)
int THSX = 0;
int THSY = 0;
int THSZ = 0;
/*
Threshold registers INT1_THS_xH and INT_THS_xL (respectively MSB and LSB) define
the reference angular rates used by interrupt generation circuitry
*/
int DURATION_EN = 0;//WAIT enable. Default value: 0 (0: disable; 1: enable)
int DURATION_D = 0; //Duration value. Default value: 000 0000
int AND_OR = 0;     
/*
  AND/OR combination of Interrupt events. Default value: 0
  (0: OR combination of interrupt events 1: AND combination of interrupt events
*/
int LIR = 0;        
/*
  Latch Interrupt Request. Default value: 0
  (0: interrupt request not latched; 1: interrupt request latched)
  Cleared by reading INT1_SRC reg
*/
int ZHIE = 0;
/*
  Enable interrupt generation on Z high event. Default value: 0
  (0: disable interrupt request; 1: enable interrupt request on measured rate value
  higher than preset threshold)
*/
int ZLIE = 0;
/*
  Enable interrupt generation on Z low event. Default value: 0
  (0: disable interrupt request; 1: enable interrupt request on measured rate value lower
  than preset threshold)
*/
int YHIE = 0;
/*
  Enable interrupt generation on Y high event. Default value: 0
  (0: disable interrupt request; 1: enable interrupt request on measured rate value
  higher than preset threshold)
*/
int YLIE = 0;
/*
  Enable interrupt generation on Y low event. Default value: 0
  (0: disable interrupt request; 1: enable interrupt request on measured rate value lower
  than preset threshold)
*/
int XHIE = 0;
/*
  Enable interrupt generation on Y high event. Default value: 0
  (0: disable interrupt request; 1: enable interrupt request on measured rate value
  higher than preset threshold)
*/
int XLIE = 0;
/*
  Enable interrupt generation on Y low event. Default value: 0
  (0: disable interrupt request; 1: enable interrupt request on measured rate value lower
  than preset threshold)
*/
//Interrupt generation

//filter table 8 and table 9
int HPen = 0;
int Out_Sel1 = 0;
int Out_Sel0 = 0;
int INT1_Sel1 = 0;
int INT1_Sel0 = 0;
int HPM = B00;
int HPCF = B0000;
//filter table 8 and t able 9

int16_t X = 0;
int16_t Y = 0;
int16_t Z = 0;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);  // start serial for output
    Wire.begin(SDA_PIN, SCL_PIN, I2C_MASTER);        // join i2c bus (address optional for master)
    delay(150);            //whait to load
    Serial.println(L3G4200D_read(0x0F));
    L3G4200D_init();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(L3G4200D_read(0x0F));
  Serial.print(" name ");
  while(L3G4200D_read(0x0F)==0){
    Serial.println("no name");
    delay(100);
    }
  //int* angular = 
  L3G4200D_read_angular_rate();

  Serial.print(L3G4200D_read_temp());
  Serial.print(" temp ");
  Serial.print(X);
  Serial.print(" x ");
  Serial.print(Y);
  Serial.print(" y ");
  Serial.print(Z);
  Serial.print(" z ");
  Serial.print(FSS);
  Serial.print(" FSS ");
  Serial.print(WTM_SRC);
  Serial.print(" WTM_SRC ");
  Serial.print(OVRN);
  Serial.print(" OVRN ");
  Serial.print(EMPTY);
  Serial.print(" EMPTY ");
  Serial.println();
  delay(100);
/*
  Serial.print(L3G4200D_read(CTRL_REG1_address));
  Serial.println(" CTRL_REG1_address ");
  Serial.print(L3G4200D_read(CTRL_REG2_address));
  Serial.println(" CTRL_REG2_address ");
  Serial.print(L3G4200D_read(CTRL_REG3_address));
  Serial.println(" CTRL_REG3_address ");
  Serial.print(L3G4200D_read(CTRL_REG4_address));
  Serial.println(" CTRL_REG4_address ");
  Serial.print(L3G4200D_read(CTRL_REG5_address));
  Serial.println(" CTRL_REG5_address ");*/
}
int8_t L3G4200D_read_temp(){
    int8_t temp = L3G4200D_read(OUT_TEMP_address);
    temp = 25 - temp
    return temp;
  }
int* L3G4200D_read_angular_rate(){
  /*
    1. Read STATUS_REG
    2. If STATUS_REG(3) = 0 then go to 1
    3. If STATUS_REG(7) = 1 then some data have been overwritten
    4. Read OUT_X_L
    5. Read OUT_X_H
    6. Read OUT_Y_L
    7. Read OUT_Y_H
    8. Read OUT_Z_L
    9. Read OUT_Z_H
    10. Data processing
    11. Go to 1
  */
  int STATUS_REG = L3G4200D_read(0x27);
  int tmp = 0 | (1<<3);
  while((STATUS_REG & tmp) == 0){
    Serial.println("weit");
    STATUS_REG = L3G4200D_read(0x27);
  }
  tmp =  L3G4200D_read(FIFO_SRC_REG_address);
  FSS = tmp & B00011111;
  WTM_SRC = tmp >> 7;
  OVRN = (tmp >> 6) & B01;
  EMPTY = (tmp >> 5) & B01;
  tmp = 0 | (1<<7);
  if(STATUS_REG & tmp == 1){Serial.println("read alarm");}
  X = (L3G4200D_read(0x29)<<8)|L3G4200D_read(0x28);
  Y = (L3G4200D_read(0x2B)<<8)|L3G4200D_read(0x2A);
  Z = (L3G4200D_read(0x2D)<<8)|L3G4200D_read(0x2C);
  int out[3] = {X,Y,Z};

  return out;
  }

void L3G4200D_init(){
  /*
    1. Write CTRL_REG2
    2. Write CTRL_REG3
    3. Write CTRL_REG4
      4. Write CTRL_REG6
    5. Write Reference
    6. Write INT1_THS
    7. Write INT1_DUR
    8. Write INT1_CFG
    9. Write CTRL_REG5
    10. Write CTRL_REG1
  */
  uint8_t CTRL_REG1 = (DR << 6)|(BW << 4)|(PD << 3)|(Zen << 2)|(Yen << 1)|Xen;
      /*  Serial.print(DR);
  Serial.println(" DR");*/
  uint8_t CTRL_REG2 = B00000000|(HPM << 4)|HPCF;
   /* Serial.print(CTRL_REG2);
  Serial.println(" CTRL_REG2");
    Serial.print(B00000000);
  Serial.println(" B00000000");
    Serial.print(HPM);
  Serial.println(" HPM");
      Serial.print(HPCF);
  Serial.println(" HPCF");*/
  uint8_t CTRL_REG3 = (I1_Int1 << 7)|(I1_Boot << 6)|(H_Lactive << 5)|(PP_OD << 4)|(I2_DRDY << 3)|(I2_WTM << 2)|(I2_ORun << 1)|I2_Empty;
  uint8_t CTRL_REG4 = (BDU << 7)|(BLE << 6)|(FS << 4)|(ST << 1)| SIM;
  uint8_t CTRL_REG5 = (BOOT << 7)|(FIFO_EN << 6)|(HPen << 4)|(INT1_Sel1 << 3)|(INT1_Sel0 << 2)|(Out_Sel1 << 1)|Out_Sel0;
  //int CTRL_REG6_address = 0x;
  int Reference = REF;
  uint8_t INT1_THS_XH = THSX >> 7;
  uint8_t INT1_THS_XL = THSX & 255;
  uint8_t INT1_THS_YH = THSY >> 7;
  uint8_t INT1_THS_YL = THSY & 255;
  uint8_t INT1_THS_ZH = THSZ >> 7;
  uint8_t INT1_THS_ZL = THSZ & 255;
  uint8_t INT1_DUR = (DURATION_EN << 7)|DURATION_D;
  uint8_t INT1_CFG = (AND_OR << 7)|(LIR << 6)|(ZHIE << 5)|(ZLIE << 4)|(YHIE << 3)|(YLIE << 2)|(XHIE << 1)|XLIE;
  uint8_t FIFO_CTRL_REG = (FM<<5)|WTM; 
 // uint8_t FIFO_SRC_REG = (WTM_SRC << 7)|(OVRN << 6)|(EMPTY << 5)|FSS; 
  Serial.print("CTRL_REG1 ");
  Serial.println(CTRL_REG1);
  Serial.print("CTRL_REG2 ");
  Serial.println(CTRL_REG2);
  Serial.print("CTRL_REG3 ");
  Serial.println(CTRL_REG3);
  Serial.print("CTRL_REG4 ");
  Serial.println(CTRL_REG4);
  Serial.print("CTRL_REG5 ");
  Serial.println(CTRL_REG5);
  L3G4200D_write(CTRL_REG2_address, CTRL_REG2);
  L3G4200D_write(CTRL_REG3_address, CTRL_REG3);
  L3G4200D_write(CTRL_REG4_address, CTRL_REG4);
  L3G4200D_write(Reference_address, Reference);
  L3G4200D_write(INT1_THS_XH_address, INT1_THS_XH);
  L3G4200D_write(INT1_THS_XL_address, INT1_THS_XL);
  L3G4200D_write(INT1_THS_YH_address, INT1_THS_YH);
  L3G4200D_write(INT1_THS_YL_address, INT1_THS_YL);
  L3G4200D_write(INT1_THS_ZH_address, INT1_THS_ZH);
  L3G4200D_write(INT1_THS_ZL_address, INT1_THS_ZL);
  L3G4200D_write(INT1_DUR_address, INT1_DUR);  
  L3G4200D_write(INT1_CFG_address, INT1_CFG);  
  L3G4200D_write(CTRL_REG5_address, CTRL_REG5);
  L3G4200D_write(CTRL_REG1_address, CTRL_REG1);  
  L3G4200D_write(FIFO_CTRL_REG_address, FIFO_CTRL_REG);
//  L3G4200D_write(FIFO_SRC_REG_address, FIFO_SRC_REG);

  }
  
void L3G4200D_write(uint8_t reg, uint8_t inf){
  Wire.beginTransmission(I2C_L3G4200D);
  Wire.write(reg);
  Wire.write(inf);
  Wire.endTransmission(true);
}

int L3G4200D_read(uint8_t reg){
  Wire.beginTransmission(I2C_L3G4200D);

  Wire.write(reg);
  Wire.endTransmission(true);
    
  Wire.requestFrom(I2C_L3G4200D,1,true);
  int out=0;
  while(Wire.available()) {
    out = Wire.read();             
  }
  return out;
}
