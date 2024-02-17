from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'TnP_L1_2023'
config.General.workArea = 'Crab'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'TnP_L1.py'
#config.JobType.allowUndistributedCMSSW = True
config.section_("Data")

config.Data.inputDataset = '/EGamma1/Run2023D-PromptReco-v1/MINIAOD'
config.Data.secondaryInputDataset= '/EGamma1/Run2023D-v1/RAW'

config.Data.inputDBS = 'global'
config.Data.runRange =  '370580'
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 15000 # number of events per jobs
config.Data.totalUnits = -999 # number of events
config.Data.outLFNDirBase = '/store/user/mkovac/Production/RUN_3/ECAL/05122023_CMSSW_13_1_0_pre2'
config.Data.publication = False
#config.Data.allowNonValidInputDataset = True
config.Data.outputDatasetTag = 'TnP_L1'
config.section_("Site")
config.Site.storageSite = 'T3_CH_CERNBOX'