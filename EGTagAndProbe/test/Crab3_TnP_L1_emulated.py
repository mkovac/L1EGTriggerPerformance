from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")

config.General.requestName = 'TnP_L1_emulated_DW_0p5'
#config.General.requestName = 'TnP_L1_emulated_DW_2p5'
#config.General.requestName = 'TnP_L1_emulated'

config.General.workArea = 'Crab'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'TnP_L1_emulated.py'
#config.JobType.allowUndistributedCMSSW = True
config.section_("Data")

config.Data.inputDataset = '/EGamma1/Run2023D-PromptReco-v1/MINIAOD'
config.Data.secondaryInputDataset= '/EGamma1/Run2023D-v1/RAW'

config.Data.inputDBS = 'global'
config.Data.runRange =  '370580'
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 15000
config.Data.totalUnits = -999 # number of events
config.Data.outLFNDirBase = '/store/user/mkovac/Production/RUN_3/ECAL/17022024_CMSSW_13_3_0/'
config.Data.publication = False
#config.Data.allowNonValidInputDataset = True

config.Data.outputDatasetTag = 'TnP_L1_emulated_DW_0p5'
#config.Data.outputDatasetTag = 'TnP_L1_emulated_DW_2p5'
#config.Data.outputDatasetTag = 'TnP_L1_emulated'

config.section_("Site")
#config.Site.whitelist = ['T3_US_FNALLPC','T2_BE_IIHE','T2_DE_RWTH','T2_US_Purdue','T2_BE_UCL','T2_US_Caltech','T2_IT_Rome','T2_US_Nebraska','T2_DE_DESY','T2_US_UCSD']
config.Site.storageSite = 'T3_CH_CERNBOX'