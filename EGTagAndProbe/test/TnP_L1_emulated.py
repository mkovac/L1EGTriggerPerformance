import FWCore.ParameterSet.VarParsing as VarParsing
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras

process = cms.Process("TagAndProbe", eras.Run3)

process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')


options = VarParsing.VarParsing ('analysis')
options.register ('secondaryFilesList','',VarParsing.VarParsing.multiplicity.singleton,VarParsing.VarParsing.varType.string,  "List of secondary input files")

options.register ('skipEvents',
                  -1, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.int,            # string, int, or float
                  "Number of events to skip")
                  
options.register ('JSONfile',
                  "", # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.string,         # string, int, or float
                  "JSON file (empty for no JSON)")
                  
                  
# Basic settings
options.outputFile = 'TnP_L1_emulated.root'
options.inputFiles = []
options.maxEvents  = -999
#options.maxEvents  = 500

options.parseArguments()

isData = True
isMiniAOD = True


###############
# Electron ID #
###############

# Load tools and function definitions
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
from RecoEgamma.ElectronIdentification.egmGsfElectronIDs_cfi import * # Not needed as it is done in the switchOnVIDElectronIdProducer line via egmGsfElectronIDs_cff
from PhysicsTools.SelectorUtils.centralIDRegistry import central_id_registry # Not needed as it is done in the switchOnVIDElectronIdProducer line via egmGsfElectronIDs_cff

process.load("RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi") # Not needed as it is done in the switchOnVIDElectronIdProducer line via egmGsfElectronIDs_cff


# Turn on VID producer and indicate data format
if isMiniAOD == True:
    dataFormat = DataFormat.MiniAOD
else:
    dataFormat = DataFormat.AOD

switchOnVIDElectronIdProducer(process, dataFormat)


process.load("RecoEgamma.ElectronIdentification.egmGsfElectronIDs_cfi") # Not needed as it is done in the switchOnVIDElectronIdProducer line via egmGsfElectronIDs_cff


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
    #electronMVAVariableHelper,
    electronMVAValueMapProducer,
    egmGsfElectronIDs
)

egmGsfElectronIDSequence = cms.Sequence(egmGsfElectronIDTask)


if isData:
   from Configuration.AlCa.autoCond import autoCond
#   process.GlobalTag.globaltag = '124X_dataRun3_Prompt_v10'
   process.GlobalTag.globaltag = '130X_dataRun3_Prompt_v4'
   
 
#================#
# Double weights #
#================#  
    
#   process.GlobalTag.toGet = cms.VPSet(
#      cms.PSet(
#    	   record = cms.string("EcalTPGOddWeightIdMapRcd"),
##    	   tag = cms.string("EcalTPG_OddWeightIdMap_delta0p5_mc"),
# 		   tag = cms.string("EcalTPG_OddWeightIdMap_delta2p5_mc"),
# 		   connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS')
# 		   ),
#      cms.PSet(
#    	   record = cms.string("EcalTPGOddWeightGroupRcd"),
# 		   tag = cms.string("EcalTPGOddWeightGroup_mc"),
# 		   connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS')
# 		   ),
#      cms.PSet(
#    	   record = cms.string("EcalTPGTPModeRcd"),
# 		   tag = cms.string("EcalTPG_TPMode_Killing_mc"),
# 		   connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS')
# 		   ),
# 		   
 		   
#============================================#
# Spike killer, linearization, and pedestals #
#============================================#
 		  
#    	cms.PSet(
#    		record = cms.string("EcalTPGSpikeRcd"),
# 			tag = cms.string("EcalTPGSpike_16"),
# 			connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS')
# 			),
# 		cms.PSet(
# 			record = cms.string("EcalTPGFineGrainStripEERcd"),
# 			tag = cms.string("EcalTPGFineGrainStrip_16"),
# 			tag = cms.string("EcalTPGFineGrainStrip_20"),
# 			tag = cms.string("EcalTPGFineGrainStrip_22"),
# 			tag = cms.string("EcalTPGFineGrainStrip_24"),
#			connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS')
# 			),
#    	cms.PSet(
#         record = cms.string("EcalTPGLinearizationConstRcd"),
#         tag = cms.string("EcalTPGLinearizationConst_IOV_319253_beginning_at_1"),
#         connect = cms.string('sqlite_file:EcalTPG_trans_319253_pedes_319111_moved_to_1.db')
#       	),
#      cms.PSet(
#         record = cms.string("EcalTPGPedestalsRcd"),
#         tag = cms.string("EcalTPGPedestals_319253_beginning_at_1"),
#         connect =cms.string('sqlite_file:EcalTPG_trans_319253_pedes_319111_moved_to_1.db')
#	      )
#	        )
       
   process.load('L1EGTriggerPerformance.EGTagAndProbe.TagAndProbe_cff')
    
   process.source = cms.Source("PoolSource",
#      fileNames = cms.untracked.vstring('/store/data/Run2022D/EGamma/MINIAOD/PromptReco-v2/000/357/734/00000/08a88559-12f4-47c8-a861-277665f2b549.root'),
      fileNames = cms.untracked.vstring('/store/data/Run2023D/EGamma1/MINIAOD/PromptReco-v1/000/370/580/00000/0147b9df-6211-4aad-8bd7-bea1d707cc2d.root'),
      secondaryFileNames = cms.untracked.vstring
		(
#         '/store/data/Run2022D/EGamma/RAW/v1/000/357/734/00000/905a7dca-7ea8-49af-a381-feeeb6132a56.root',
#         '/store/data/Run2022D/EGamma/RAW/v1/000/357/734/00000/9ccb8857-69df-4573-86f2-39c917e74f06.root',
#         '/store/data/Run2022D/EGamma/RAW/v1/000/357/734/00000/9e3e6858-a2e2-4888-927e-6b54c2562cd8.root',
#         '/store/data/Run2022D/EGamma/RAW/v1/000/357/734/00000/d79b7867-1b0e-453c-8c94-8f74234f4eb9.root'
         
         '/store/data/Run2023D/EGamma1/RAW/v1/000/370/580/00000/4a14b243-0383-4a69-a50c-3a096d37abfe.root',
         '/store/data/Run2023D/EGamma1/RAW/v1/000/370/580/00000/7632221d-6dd3-4dc9-a35f-997aa127d10c.root',
         '/store/data/Run2023D/EGamma1/RAW/v1/000/370/580/00000/7a9c6da6-9ac2-4ba7-a52f-b229cf3665fc.root',
         '/store/data/Run2023D/EGamma1/RAW/v1/000/370/580/00000/81971e2e-14d7-4d00-8a97-a6f277c5f498.root',
         '/store/data/Run2023D/EGamma1/RAW/v1/000/370/580/00000/8c253537-665a-4edb-ac1d-b77020428d03.root',
         '/store/data/Run2023D/EGamma1/RAW/v1/000/370/580/00000/8ef7dfb4-9d47-4d9c-9c95-75c18a6c3713.root',
         '/store/data/Run2023D/EGamma1/RAW/v1/000/370/580/00000/a463893d-3a4a-4bc3-8138-f6ecaee76704.root',
         '/store/data/Run2023D/EGamma1/RAW/v1/000/370/580/00000/c7ac4614-d23e-445a-bee3-fca54ab7d653.root',
         '/store/data/Run2023D/EGamma1/RAW/v1/000/370/580/00000/d74fe74d-27b5-4137-b766-4a686602d2d7.root',
         '/store/data/Run2023D/EGamma1/RAW/v1/000/370/580/00000/e11cd178-e453-4653-8591-1821d37f24af.root'
      )
   )
else:
   process.GlobalTag.globaltag = '106X_mcRun2_asymptotic_preVFP_v5'
   process.load('EGTagAndProbe.EGTagAndProbe.MCanalysis_cff')
   process.source = cms.Source("PoolSource",
      fileNames = cms.untracked.vstring(
	      '/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/MINIAODSIM/PU25ns_106X_mcRun2_asymptotic_preVFP_v5_UL16hltval_preVFP_v5-v1/10000/CCB6A88B-A1DE-4044-910A-B548D565AFC4.root'),
      secondaryFileNames = cms.untracked.vstring(
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/A255DD0A-714F-EA11-BCEB-0CC47A4D75EC.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/00FDEC5B-4C4F-EA11-8B31-0025905B85D6.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/10EBA3B3-444F-EA11-9328-AC1F6BAC7D10.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/366241A5-454F-EA11-B7C6-0CC47A4D75F2.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/3EB877C6-494F-EA11-BF42-0CC47A4D7600.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/40E0EA66-484F-EA11-B6E5-0025905A612E.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/4436D4C2-494F-EA11-A1C9-0CC47A4C8F18.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/4A55CE2B-764F-EA11-A940-0CC47A4D76C6.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/F041AF46-4C4F-EA11-A210-0CC47A7452DA.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/D0413658-514F-EA11-A0DA-0025905B85F6.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/EADA2848-614F-EA11-AF89-0025905B8598.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/8CD19F06-664F-EA11-9280-0CC47A4D7628.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/8CD7B387-4D4F-EA11-839A-0025905B85D6.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/BC9CA916-6A4F-EA11-BD3D-AC1F6BAC7C2A.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/EE735DDC-464F-EA11-A8CE-0CC47A7C3408.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/CEF45DE6-7B4F-EA11-B9EF-0CC47A7C354C.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/BC234A3D-494F-EA11-A2D2-0CC47A4C8E28.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/4ABB1E6C-484F-EA11-9F80-0025905A48FC.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/7CA13DCE-864F-EA11-A60C-AC1F6BAC7D14.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/50A5D0F3-644F-EA11-91DC-AC1F6BAC807A.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/5698404B-904F-EA11-89F5-0CC47A4D7646.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/7ADA49E9-414F-EA11-B0E3-AC1F6BAC7C78.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/7E787757-634F-EA11-91F1-0CC47A4D7690.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/8E11FA7C-624F-EA11-9696-0CC47A7C35D8.root',
		'/store/relval/CMSSW_10_6_8/RelValZEE_13UP16/GEN-SIM-RAW/PU25ns_80X_mcRun2_asymptotic_v20_UL16hltval_preVFP_v5-v1/10000/B4732519-6D4F-EA11-867E-0025905B85AE.root'
      )
   )
   
   # In case no HLT object in MC sample considered or you're fed up with trying to find the right HLT collections
   process.Ntuplizer.useHLTMatch = cms.bool(False)

if isMiniAOD:
    process.Ntuplizer.electrons = cms.InputTag("slimmedElectrons")
    process.Ntuplizer.genParticles = cms.InputTag("prunedGenParticles")
    process.Ntuplizer.Vertices = cms.InputTag("offlineSlimmedPrimaryVertices")

process.schedule = cms.Schedule()


# L1 emulation stuff

if isData:
    from L1Trigger.Configuration.customiseReEmul import L1TReEmulFromRAWsimEcalTP 
    process = L1TReEmulFromRAWsimEcalTP(process)
else:
    from L1Trigger.Configuration.customiseReEmul import L1TReEmulMCFromRAW
    process = L1TReEmulMCFromRAW(process) 
    from L1Trigger.Configuration.customiseUtils import L1TTurnOffUnpackStage2GtGmtAndCalo 
    process = L1TTurnOffUnpackStage2GtGmtAndCalo(process)


#process.load("L1Trigger.L1TCalorimeter.caloParams_2021_v0_2_cfi")
process.load("L1Trigger.L1TCalorimeter.caloParams_2023_v0_4_cfi")


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

process.p = cms.Path (
   process.egmGsfElectronIDSequence +
   process.RawToDigi +
   process.L1TReEmul +
   process.NtupleSeq
)

process.schedule = cms.Schedule(process.p)

# Silence output
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10

# Adding ntuplizer
process.TFileService=cms.Service('TFileService',fileName=cms.string(options.outputFile))
