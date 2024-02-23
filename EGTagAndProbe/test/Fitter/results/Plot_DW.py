import ROOT
import TurnOnPlot_DATA as TurnOnPlot
from ROOT import RooCurve, RooHist, RooAbsData

ROOT.gROOT.SetBatch(True)
#ROOT.gInterpreter.AddIncludePath("./include")
ROOT.gSystem.Load("/afs/cern.ch/work/m/mkovac/CMS/RUN_3/ECAL/CMSSW_13_3_0/src/L1EGTriggerPerformance/EGTagAndProbe/test/Fitter/obj/FuncCB_cpp.so")


#========#
# DW_2p5 #
#========#

path = "./RootFiles/DoubleWeights/DW_2p5/"
plotPath = "Plots/DoubleWeights/DW_2p5/Default_vs_emulated_"

#emulation = "DW_2p5_hasL1Emu_10"
#emulation = "DW_2p5_hasL1Emu_iso10"

#emulation = "DW_2p5_hasL1Emu_20"
#emulation = "DW_2p5_hasL1Emu_iso20"

emulation = "DW_2p5_hasL1Emu_30"
#emulation = "DW_2p5_hasL1Emu_iso30"

#emulation = "DW_2p5_hasL1Emu_40"
#emulation = "DW_2p5_hasL1Emu_iso40"
#emulation = "DW_2p5_hasL1Emu_tightiso40"
#emulation = "DW_2p5_hasL1Emu_looseiso40"



#========#
# DW_0p5 #
#========#

#path = "./RootFiles/DoubleWeights/DW_0p5/"
#plotPath = "Plots/DoubleWeights/DW_0p5/Emulated_vs_emulated_"

#emulation = "DW_0p5_hasL1Emu_10"
#emulation = "DW_0p5_hasL1Emu_iso10"

#emulation = "DW_0p5_hasL1Emu_20"
#emulation = "DW_0p5_hasL1Emu_iso20"

#emulation = "DW_0p5_hasL1Emu_30"
#emulation = "DW_0p5_hasL1Emu_iso30"


#emulation = "DW_0p5_hasL1Emu_40"
#emulation = "DW_0p5_hasL1Emu_iso40"


inputFile = ROOT.TFile.Open(path + "Default_vs_emulated_" + emulation + ".root")


#========#
#  Test  #
#========#

#path = "./RootFiles/Test/"
#plotPath = "./Plots/Test/Default_vs_emulated_"

#emulation = "default"
#emulation = "default_emul_script"

#inputFile = ROOT.TFile.Open(path + "Default_vs_emulated_" + emulation + ".root")



plots = []
plots.append(TurnOnPlot.TurnOnPlot())
plots[-1].name = "Efficiency"
plots[-1].xRange = (5, 1000)
plots[-1].legendPosition = (0.6, 0.2, 0.9, 0.4)
plots[-1].plotDir = plotPath + emulation

plots.append(TurnOnPlot.TurnOnPlot())
plots[-1].name = "Efficiency_difference"
plots[-1].xRange = (5, 1000)
plots[-1].legendPosition = (0.45, 0.2, 0.9, 0.3)
plots[-1].plotDir = plotPath + emulation


histo = inputFile.Get("histo_Default")
histo.__class__ = ROOT.RooHist
	
fit   = inputFile.Get("fit_Default")
fit.__class__ = ROOT.RooCurve

turnon = TurnOnPlot.TurnOn(Name="Stage2", Histo=histo, Fit=fit,
                                    MarkerColor=ROOT.kBlack, MarkerStyle=21, LineColor=ROOT.kBlack, LineStyle=1,
#                                    Legend="Default conditions: TnP_L1_emulated.py")
                                    Legend="Default")

histo2 = inputFile.Get("histo_Emulated")
histo2.__class__ = ROOT.RooHist
	
fit2   = inputFile.Get("fit_Emulated")
fit2.__class__ = ROOT.RooCurve

turnon2 = TurnOnPlot.TurnOn(Name="Stage2", Histo=histo2, Fit=fit2,
                                    MarkerColor=ROOT.kRed, MarkerStyle=20, LineColor=ROOT.kRed, LineStyle=1,
                                    Legend="Emulated " + "("+ emulation +")")
#                                    Legend="Emulated (Default conditions)")                                    

plots[0].addTurnOn(turnon)
plots[0].addTurnOn(turnon2)


#Plot the difference:
diffcurve=RooCurve("diff","diff",fit, fit2, 1,-1)
diffhist=RooHist(histo,histo2,1,-1,RooAbsData.SumW2)
turnondiff = TurnOnPlot.TurnOn(Name="Stage2", Histo=diffhist, Fit=diffcurve,
                                    MarkerColor=ROOT.kBlack, MarkerStyle=20, LineColor=ROOT.kBlue,LineStyle=1,
                                    Legend="Default-DW")

plots[1].addTurnOn(turnondiff)


canvas = []
for plot in plots:
    canvas.append(plot.plot())

inputFile.Close()