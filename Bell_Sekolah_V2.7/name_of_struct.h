struct Waktu
{
  byte jam;
  byte menit;
};

struct TabelMataPelajaran
{
  byte aktif;
  Waktu waktu;
  byte hariAktif;
  byte kegiatan;
};

const char kegiatanText[][17] PROGMEM = {
  "-               ",
  "Jam Pelajaran 1 ",
  "Jam Pelajaran 2 ",
  "Jam Pelajaran 3 ",
  "Jam Pelajaran 4 ",
  "Jam Pelajaran 5 ",
  "Jam Pelajaran 6 ",
  "Jam Pelajaran 7 ",
  "Jam Pelajaran 8 ",
  "Jam Pelajaran 9 ",
  "Upacara         ",
  "Istirahat       ",
  "Istirahat1      ",
  "Istirahat2      ",
  "Pulang          ",
  "Pulang Akh Pekan",
  "0018-Costum1    ",
  "0019-Costum2    ",
  "0020-Costum3    ",
  "0021-Costum4    ",
  "0022-Costum5    ",
  "0023-Costum6    ",
  "0024-Costum7    ",
  "0025-Costum8    ",
  "0026-Costum9    ",
  "0027-Costum10   ",
  "0028-Costum11   ",
  "0029-Costum12   ",
  "0030-Costum13   ",
  "0031-Costum14   ",
  "0032-Costum15   ",
  "0033-Costum16   ",
  "0034-Costum17   ",
  "0035-Costum18   ",
  "0036-Costum19   ",
  "0037-Costum20   ",
  "0038-Costum21   ",
  "0039-Costum22   ",
  "0040-Costum23   ",
  "0041-Costum24   ",
  "0042-Costum25   ",
  "0043-Costum26   ",
  "0044-Costum27   ",
  "0045-Costum28   ",
  "0046-Costum29   ",
  "0047-Costum30   ",
  "0048-Costum31   ",
  "0049-Costum32   ",
  "0050-Costum33   ",
  "0051-Costum34   ",
  "0052-Costum35   ",
  "0053-Costum36   ",
  "0054-Costum37   ",
  "0055-Costum38   ",
  "0056-Costum39   ",
  "0057-Costum40   ",
  "0058-Costum41   ",
  "0059-Costum42   ",
  "0060-Costum43   ",
  "0061-Costum44   ",
  "0062-Costum45   ",
  "0063-Costum46   ",
  "0064-Costum47   ",
  "0065-Costum48   ",
  "0066-Costum49   ",
  "0067-Costum50   ",
  "0068-Costum51   ",
  "0069-Costum52   ",
  "0070-Costum53   ",
  "0071-Costum54   ",
  "0072-Costum55   ",
  "0073-Costum56   ",
  "0074-Costum57   ",
  "0075-Costum58   ",
  "0076-Costum59   ",
  "0077-Costum60   ",
  "0078-Costum61   ",
  "0079-Costum62   ",
  "0080-Costum63   ",
  "0081-Costum64   ",
  "0082-Costum65   ",
  "0083-Costum66   ",
  "0084-Costum67   ",
  "0085-Costum68   ",
  "0086-Costum69   ",
  "0087-Costum70   ",
  "0088-Costum71   ",
  "0089-Costum72   ",
  "0090-Costum73   ",
  "0091-Costum74   ",
  "0092-Costum75   ",
  "0093-Costum76   ",
  "0094-Costum77   ",
  "0095-Costum78   ",
  "0096-Costum79   ",
  "0097-Costum80   ",
  "0098-Costum81   ",
  "0099-Costum82   ",
  "0100-Costum83   ",
  "0101-Costum84   ",
  "0102-Costum85   ",
  "0103-Costum86   ",
  "0104-Costum87   ",
  "0105-Costum88   ",
  "0106-Costum89   ",
  "0107-Costum90   ",
  "0108-Costum91   ",
  "0109-Costum92   ",
  "0110-Costum93   ",
  "0111-Costum94   ",
  "0112-Costum95   ",
  "0113-Costum96   ",
  "0114-Costum97   ",
  "0115-Costum98   ",
  "0116-Costum99   ",
  "0117-Costum100  ",
  "0118-Costum101  ",
  "0119-Costum102  ",
  "0120-Costum103  ",
  "0121-Costum104  ",
  "0122-Costum105  ",
  "0123-Costum106  ",
  "0124-Costum107  ",
  "0125-Costum108  ",
  "0126-Costum109  ",
  "0127-Costum110  ",
  "0128-Costum111  ",
  "0129-Costum112  ",
  "0130-Costum113  ",
  "0131-Costum114  ",
  "0132-Costum115  ",
  "0133-Costum116  ",
  "0134-Costum117  ",
  "0135-Costum118  ",
  "0136-Costum119  ",
  "0137-Costum120  ",
  "0138-Costum121  ",
  "0139-Costum122  ",
  "0140-Costum123  ",
  "0141-Costum124  ",
  "0142-Costum125  ",
  "0143-Costum126  ",
  "0144-Costum127  ",
  "0145-Costum128  ",
  "0146-Costum129  ",
  "0147-Costum130  ",
  "0148-Costum131  ",
  "0149-Costum132  ",
  "0150-Costum133  ",
  "0151-Costum134  ",
  "0152-Costum135  ",
  "0153-Costum136  ",
  "0154-Costum137  ",
  "0155-Costum138  ",
  "0156-Costum139  ",
  "0157-Costum140  ",
  "0158-Costum141  ",
  "0159-Costum142  ",
  "0160-Costum143  ",
  "0161-Costum144  ",
  "0162-Costum145  ",
  "0163-Costum146  ",
  "0164-Costum147  ",
  "0165-Costum148  ",
  "0166-Costum149  ",
  "0167-Costum150  ",
  "0168-Costum151  ",
  "0169-Costum152  ",
  "0170-Costum153  ",
  "0171-Costum154  ",
  "0172-Costum155  ",
  "0173-Costum156  ",
  "0174-Costum157  ",
  "0175-Costum158  ",
  "0176-Costum159  ",
  "0177-Costum160  ",
  "0178-Costum161  ",
  "0179-Costum162  ",
  "0180-Costum163  ",
  "0181-Costum164  ",
  "0182-Costum165  ",
  "0183-Costum166  ",
  "0184-Costum167  ",
  "0185-Costum168  ",
  "0186-Costum169  ",
  "0187-Costum170  ",
  "0188-Costum171  ",
  "0189-Costum172  ",
  "0190-Costum173  ",
  "0191-Costum174  ",
  "0192-Costum175  ",
  "0193-Costum176  ",
  "0194-Costum177  ",
  "0195-Costum178  ",
  "0196-Costum179  ",
  "0197-Costum180  ",
  "0198-Costum181  ",
  "0199-Costum182  ",
  "0200-Costum183  "
};

enum _kegiatan
{
  TidakAda,
  JamPelajaran1,
  JamPelajaran2,
  JamPelajaran3,
  JamPelajaran4,
  JamPelajaran5,
  JamPelajaran6,
  JamPelajaran7,
  JamPelajaran8,
  JamPelajaran9,
  Upacara,
  Istirahat,
  Istirahat1,
  Istirahat2,
  Pulang,
  PulangAkhPekan,
  Costum1,
  Costum2,
  Costum3,
  Costum4,
  Costum5,
  Costum6,
  Costum7,
  Costum8,
  Costum9,
  Costum10,
  Costum11,
  Costum12,
  Costum13,
  Costum14,
  Costum15,
  Costum16,
  Costum17,
  Costum18,
  Costum19,
  Costum20,
  Costum21,
  Costum22,
  Costum23,
  Costum24,
  Costum25,
  Costum26,
  Costum27,
  Costum28,
  Costum29,
  Costum30,
  Costum31,
  Costum32,
  Costum33,
  Costum34,
  Costum35,
  Costum36,
  Costum37,
  Costum38,
  Costum39,
  Costum40,
  Costum41,
  Costum42,
  Costum43,
  Costum44,
  Costum45,
  Costum46,
  Costum47,
  Costum48,
  Costum49,
  Costum50,
  Costum51,
  Costum52,
  Costum53,
  Costum54,
  Costum55,
  Costum56,
  Costum57,
  Costum58,
  Costum59,
  Costum60,
  Costum61,
  Costum62,
  Costum63,
  Costum64,
  Costum65,
  Costum66,
  Costum67,
  Costum68,
  Costum69,
  Costum70,
  Costum71,
  Costum72,
  Costum73,
  Costum74,
  Costum75,
  Costum76,
  Costum77,
  Costum78,
  Costum79,
  Costum80,
  Costum81,
  Costum82,
  Costum83,
  Costum84,
  Costum85,
  Costum86,
  Costum87,
  Costum88,
  Costum89,
  Costum90,
  Costum91,
  Costum92,
  Costum93,
  Costum94,
  Costum95,
  Costum96,
  Costum97,
  Costum98,
  Costum99,
  Costum100,
  Costum101,
  Costum102,
  Costum103,
  Costum104,
  Costum105,
  Costum106,
  Costum107,
  Costum108,
  Costum109,
  Costum110,
  Costum111,
  Costum112,
  Costum113,
  Costum114,
  Costum115,
  Costum116,
  Costum117,
  Costum118,
  Costum119,
  Costum120,
  Costum121,
  Costum122,
  Costum123,
  Costum124,
  Costum125,
  Costum126,
  Costum127,
  Costum128,
  Costum129,
  Costum130,
  Costum131,
  Costum132,
  Costum133,
  Costum134,
  Costum135,
  Costum136,
  Costum137,
  Costum138,
  Costum139,
  Costum140,
  Costum141,
  Costum142,
  Costum143,
  Costum144,
  Costum145,
  Costum146,
  Costum147,
  Costum148,
  Costum149,
  Costum150,
  Costum151,
  Costum152,
  Costum153,
  Costum154,
  Costum155,
  Costum156,
  Costum157,
  Costum158,
  Costum159,
  Costum160,
  Costum161,
  Costum162,
  Costum163,
  Costum164,
  Costum165,
  Costum166,
  Costum167,
  Costum168,
  Costum169,
  Costum170,
  Costum171,
  Costum172,
  Costum173,
  Costum174,
  Costum175,
  Costum176,
  Costum177,
  Costum178,
  Costum179,
  Costum180,
  Costum181,
  Costum182,
  Costum183,
};


enum PengaturanAndroid
{
  cekAses,
  pengaturanJadwal,
  pengaturanWaktu,
  testMp3,
  settings
};

char karakterMusik[8] = {
  0b00000,
  0b00100,
  0b00110,
  0b00101,
  0b00101,
  0b00100,
  0b11100,
  0b11100
};
byte karakterDetik1[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
byte karakterDetik2[8] = {
  0b00000,
  0b00000,
  0b00100,
  0b01010,
  0b00100,
  0b00000,
  0b00000,
  0b00000
};
byte karakterDetik3[8] = {
  0b00000,
  0b00100,
  0b01010,
  0b10001,
  0b01010,
  0b00100,
  0b00000,
  0b00000
};
byte karakterSetting[8] = {
  0b00100,
  0b10110,
  0b01111,
  0b00101,
  0b00110,
  0b01101,
  0b10110,
  0b00100
};
byte karakterrelay[8] =
{
  0b00001,
  0b01100,
  0b10101,
  0b10111,
  0b10111,
  0b10101,
  0b01100,
  0b00001
};

#define hariAktifSenin 1<<6
#define hariAktifSelasa 1<<5
#define hariAktifRabu 1<<4
#define hariAktifKamis 1<<3
#define hariAktifJumat 1<<2
#define hariAktifSabtu 1<<1
#define hariAktifMinggu 1<<7
#define _hariAktif(Sen,Sel,Rab,Kam,Jum,Sab,Mgu) (Mgu<<7)|(Sen<<6)|(Sel<<5)|(Rab<<4)|(Kam<<3)|(Jum<<2)|(Sab<<1)
//#define _mingguAktif(Mgu1,Mgu2,Mgu3,Mgu4,Mgu5) (Mgu1<<7)|(Mgu2<<6)|(Mgu3<<5)|(Mgu4<<4)|(Mgu5<<3)
#define _waktu(Jam, Menit) {Jam, Menit}
#define Aktif 1
#define TidakAktif 0
TabelMataPelajaran jadwalBelajar[51];
Waktu waktu;
Waktu jadwalBerikutnya;