# EGTagAndProbe
Set of tools to evaluate L1EG trigger performance on TnP

Taken from https://gitlab.cern.ch/ckoraka/EGTagAndProbe

# Install instructions
To run on 2023 data follow L1 Trigger Emulator Stage 2 Upgrade Instructions located here [1], and also given bellow

```
cmsrel CMSSW_13_3_0
cd CMSSW_13_3_0/src
cmsenv
git cms-init
git cms-addpkg L1Trigger/L1TCalorimeter
git cms-addpkg L1Trigger/L1TNtuples
git cms-addpkg L1Trigger/Configuration
git cms-addpkg L1Trigger/L1TGlobal
git cms-addpkg L1Trigger/L1TCommon
git cms-addpkg L1Trigger/L1TZDC
mkdir L1Trigger/L1TZDC/data
cd L1Trigger/L1TZDC/data
wget https://raw.githubusercontent.com/cms-data/L1Trigger-L1TCalorimeter/master/zdcLUT_HI_v0_1.txt
cd -
git clone https://github.com/cms-l1t-offline/L1Trigger-L1TCalorimeter.git L1Trigger/L1TCalorimeter/data
git cms-checkdeps -A -a
scram b -j 8 
```

Then clone the repository:
```
git clone https://github.com/mkovac/L1EgammaPerformance.git
scram b -j 8
```
Now you have set up the work directory. You should go to the L1EgammaPerformance/EGTagAndProbe/test directory and run scripts there. 


### Producing TagAndProbe nTuples with emulated L1EG
Here is a checklist of code you need to modify in order to run your desired process.
+ Update electron ID.
+ Make sure you use L1TReEmulFromRawsimEcalTP(process) instead of L1TReEmulFromRaw(process).
Corresponding lines in TnP_emulate_L1.py are:
```
from L1Trigger.Configuration.customiseReEmul import L1TReEmulFromRAWsimEcalTP
process = L1TReEmulFromRAWsimEcalTP(process)
```
+ Use the correct Calo parameters which are set in the line:```process.load("L1Trigger.L1TCalorimeter.caloParams_2023_v0_4_cfi")``` in the TnP_emulate_L1.py.
+ Be sure to use the correct sqlite file (with extension .db) in your TnP_emulate_L1.py


### Submit job on the Grid
Modify Crab3_TnP_<>.py: change requestName, inputDataSet, outLFNDirBase, outputDatasetTag, storageSite
```
voms-proxy-init -voms cms
crab submit -c Crab3_TnP_<>.py
```

### Producing turn-on plots
Create configuration file based on $CMSSW_BASE/src/L1EgammaPerformance/TagAndProbe/test/fitter/run/Parameters_16_16.par
```
cd $CMSSW_BASE/src/L1EgammaPerformance/EGTagAndProbe/test/fitter
make clean
make
./fit.exe run/Parameters_16_16.par
```
Note that you need to modify the input file location in the .par file.

Create plotting script based on $CMSSW_BASE/src/L1EgammaPerformance/EGTagAndProbe/test/fitter/results/plot_EG_16_16.py
```
cd $CMSSW_BASE/src/L1EgammaPerformance/EGTagAndProbe/test/fitter/results
python plot_EG_16_16.py
```