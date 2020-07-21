# newsubaru_2020july
Utilities for NewSUBARU exp.

## Requirements
- make command
- g++ compiler (>= C++11?)
- CERN ROOT

## How to clone it
On the terminal, clone the program.
```
$ git clone https://github.com/tamiigr/newsubaru_2020july
$ ls
$ ... newsubaru_2020july ...
$ cd newsubaru_2020july
$ ls
$ Makefile  README.md  hist.cc  nai_laser_on_off.cc  read.cc  read.h  run.sh
```

## How to compile it
On the terminal,
```
$ ls
$ Makefile  README.md  hist.cc  nai_laser_on_off.cc  read.cc  read.h  run.sh
$ make
g++ -pthread -std=c++11 -m64 -I/home/kobayash/cern/root_v6.18.04/include -c nai_laser_on_off.cc
g++ -pthread -std=c++11 -m64 -I/home/kobayash/cern/root_v6.18.04/include -o nai_laser_on_off nai_laser_on_off.o -L/home/kobayash/cern/root_v6.18.04/lib -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic
g++ -pthread -std=c++11 -m64 -I/home/kobayash/cern/root_v6.18.04/include -c hist.cc
g++ -pthread -std=c++11 -m64 -I/home/kobayash/cern/root_v6.18.04/include -o hist hist.o -L/home/kobayash/cern/root_v6.18.04/lib -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic
g++ -pthread -std=c++11 -m64 -I/home/kobayash/cern/root_v6.18.04/include -c read.cc
g++ -pthread -std=c++11 -m64 -I/home/kobayash/cern/root_v6.18.04/include -o read read.o -L/home/kobayash/cern/root_v6.18.04/lib -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic
$ ls
Makefile   hist     hist.o	      nai_laser_on_off.cc  read     read.h  run.sh
README.md  hist.cc  nai_laser_on_off  nai_laser_on_off.o   read.cc  read.o
```
## How to use it
Copy the raw data
```
$ cp <usb memory>/fed_0032_000000 ./
$ ls
$ Makefile  README.md  nai_laser_on_off  nai_laser_on_off.cc  nai_laser_on_off.o  fed_0032_000000
```
Analyse the data
```
$ ./nai_laser_on_off ./fed_0032_000000
Input filename  : ./fed_0032_000000
Output filename : ./fed_0032_000000.root
Size of a single event: 10 bytes
Event: 0x00000000000186a0, Position: 0x00000000000f4236 (999990) bytes
Event: 0x0000000000030d40, Position: 0x00000000001e8476 (1999990) bytes
Event: 0x00000000000493e0, Position: 0x00000000002dc6b6 (2999990) bytes
Event: 0x0000000000061a80, Position: 0x00000000003d08f6 (3999990) bytes
...
```

## How to see the tree in the ROOT file
```
$ root fed_0032_000000.root
root [0] 
root [1] .ls
TFile**		fed_0032_000000.root	
 TFile*		fed_0032_000000.root	
  KEY: TTree	tr;7	tr
  KEY: TTree	tr;6	tr
root [2] tr->Print()
******************************************************************************
*Tree    :tr        : tr                                                     *
*Entries : 40156001 : Total =       562428853 bytes  File  Size =  205140043 *
*        :          : Tree compression factor =   2.74                       *
******************************************************************************
*Br    0 :abs       : abs/l                                                  *
*Entries : 40156001 : Total  Size=  321381721 bytes  File Size  =  140289315 *
*Baskets :     1516 : Basket Size=    7314432 bytes  Compression=   2.29     *
*............................................................................*
*Br    1 :pha       : pha/s                                                  *
*Entries : 40156001 : Total  Size=   80348375 bytes  File Size  =   52388424 *
*Baskets :      410 : Basket Size=    1828864 bytes  Compression=   1.53     *
*............................................................................*
*Br    2 :ch        : ch/s                                                   *
*Entries : 40156001 : Total  Size=   80347961 bytes  File Size  =   11024565 *
*Baskets :      410 : Basket Size=    1828864 bytes  Compression=   7.29     *
*............................................................................*
*Br    3 :laser_on  : laser_on/s                                             *
*Entries : 40156001 : Total  Size=   80350445 bytes  File Size  =    1411046 *
*Baskets :      410 : Basket Size=    1828864 bytes  Compression=  56.94     *
*............................................................................*
root [3] tr->Scan()
************************************************************
*    Row   *       abs *       pha *        ch *  laser_on *
************************************************************
*        0 *       778 *       944 *         0 *         1 *
*        1 *      1074 *       120 *         7 *         1 *
*        2 *      2717 *       916 *         7 *         1 *
*        3 *     25778 *       944 *         0 *         1 *
*        4 *     27719 *       501 *         7 *         1 *
*        5 *     38822 *       350 *         7 *         1 *
*        6 *     50778 *       944 *         0 *         1 *
*        7 *     50749 *      2016 *         7 *         1 *
*        8 *     52716 *      1421 *         7 *         1 *
*        9 *     57516 *        56 *         7 *         1 *
*       10 *     71165 *        81 *         7 *         1 *
*       11 *     75779 *       944 *         0 *         1 *
*       12 *     77718 *       936 *         7 *         1 *
*       13 *     92422 *       593 *         7 *         1 *
*       14 *     99062 *       155 *         7 *         1 *
...
root [4] tr->Draw("pha","ch==7&&laser_on==1")
```

## Get the mean channel for the NaI spectrum
```
$ ./read fed_0032_000000.root
Read file name : fed_0032_000000.root
+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
Mean value(ch) using root class : 785.243
Mean value(ch) calculation : 785.717
+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
TApplication::GetOptions
$ 
$ root fed_0032_000000_his.root
You can see a histogram after background subtraction
```
