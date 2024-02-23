import FWCore.ParameterSet.VarParsing as VarParsing
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Config as cms

process = cms.Process("TagAndProbe")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")


options = VarParsing.VarParsing ('analysis')

options.register ('skipEvents',
                  -1, # Default value
                  VarParsing.VarParsing.multiplicity.singleton, # Singleton or list
                  VarParsing.VarParsing.varType.int,            # string, int, or float
                  "Number of events to skip")
                  
options.register ('JSONfile',
                  "", # Default value
                  VarParsing.VarParsing.multiplicity.singleton, # Singleton or list
                  VarParsing.VarParsing.varType.string,         # string, int, or float
                  "JSON file (empty for no JSON)")

# Basic settings                
options.outputFile = 'TnP_L1.root'
options.inputFiles = []
options.maxEvents  = -999
#options.maxEvents  = 500

options.parseArguments()

isData = True
isMiniAOD = True


###############
# Electron ID #
###############

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
from RecoEgamma.ElectronIdentification.egmGsfElectronIDs_cfi import * # Not needed as it is done in the switchOnVIDElectronIdProducer line via egmGsfElectronIDs_cff
from PhysicsTools.SelectorUtils.centralIDRegistry import central_id_registry # Not needed as it is done in the switchOnVIDElectronIdProducer line via egmGsfElectronIDs_cff
process.load("RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi") # Check if needed!!!


# Turn on VID producer and indicate data format
if isMiniAOD == True:
    dataFormat = DataFormat.MiniAOD
else:
    dataFormat = DataFormat.AOD
    
switchOnVIDElectronIdProducer(process, dataFormat)

process.load("RecoEgamma.ElectronIdentification.egmGsfElectronIDs_cfi") # Check if needed!!

if isMiniAOD:
    process.egmGsfElectronIDs.physicsObjectSrc = cms.InputTag('slimmedElectrons')

from PhysicsTools.SelectorUtils.centralIDRegistry import central_id_registry
process.egmGsfElectronIDSequence = cms.Sequence(process.egmGsfElectronIDs)

# Define which IDs we want to produce
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_iso_V1_cff'] 

# Add them to the VID producer
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

from RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi import * # Not needed as it is done in the switchOnVIDElectronIdProducer line via egmGsfElectronIDs_cff

egmGsfElectronIDTask = cms.Task(
    electronMVAValueMapProducer,
    egmGsfElectronIDs
)

egmGsfElectronIDSequence = cms.Sequence(egmGsfElectronIDTask)


if isData:
   from Configuration.AlCa.autoCond import autoCond
   process.GlobalTag.globaltag = '130X_dataRun3_Prompt_v4'
   process.load('L1EGTriggerPerformance.EGTagAndProbe.TagAndProbe_cff')
   process.source = cms.Source("PoolSource",
#      fileNames = cms.untracked.vstring('/store/data/Run2022D/EGamma/MINIAOD/PromptReco-v2/000/357/734/00000/08a88559-12f4-47c8-a861-277665f2b549.root')
      fileNames = cms.untracked.vstring('/store/data/Run2023D/EGamma1/MINIAOD/PromptReco-v1/000/370/580/00000/0147b9df-6211-4aad-8bd7-bea1d707cc2d.root')
   )
else:
   process.GlobalTag.globaltag = '106X_mcRun2_asymptotic_preVFP_v6'
   process.load('L1EGTriggerPerformance.EGTagAndProbe.MCanalysis_cff')
   process.source = cms.Source("PoolSource",
      fileNames = cms.untracked.vstring(
      '/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/MINIAODSIM/PU25ns_106X_mcRun2_asymptotic_preVFP_v5_UL16hltval_preVFP_v5-v1/10000/362B166F-348C-1948-B1BB-F26AEABED9FB.root')
   )
   # In case no HLT object in MC sample considered or you're fed up with trying to find the right HLT collections
   process.Ntuplizer.useHLTMatch = cms.bool(False)


if isMiniAOD:
    process.Ntuplizer.electrons = cms.InputTag("slimmedElectrons")
    process.Ntuplizer.genParticles = cms.InputTag("prunedGenParticles")
    process.Ntuplizer.Vertices = cms.InputTag("offlineSlimmedPrimaryVertices")

if options.JSONfile:
    print ("Using JSON: " , options.JSONfile)
    process.source.lumisToProcess = LumiList.LumiList(filename = options.JSONfile).getVLuminosityBlockRange()

if options.inputFiles:
    process.source.fileNames = cms.untracked.vstring(options.inputFiles)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

if options.maxEvents >= -1:
    process.maxEvents.input = cms.untracked.int32(options.maxEvents)
if options.skipEvents >= 0:
    process.source.skipEvents = cms.untracked.uint32(options.skipEvents)

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

process.p = cms.Path(
    process.egmGsfElectronIDSequence +
    process.NtupleSeq
)

# Silence output
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 500

# Adding ntuplizer
process.TFileService=cms.Service('TFileService',fileName=cms.string(options.outputFile))
