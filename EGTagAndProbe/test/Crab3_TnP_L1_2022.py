from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'TnP_L1'
config.General.workArea = 'Crab'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'TnP_L1.py'
#config.JobType.allowUndistributedCMSSW = True
config.section_("Data")

config.Data.inputDataset = '/EGamma/Run2022D-PromptReco-v2/MINIAOD'
config.Data.secondaryInputDataset= '/EGamma/Run2022D-v1/RAW'

config.Data.inputDBS = 'global'
config.Data.runRange =  '357898'
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 10000 # number of events per jobs
config.Data.totalUnits = -1 # number of event
config.Data.outLFNDirBase = '/store/user/mkovac/Production/RUN_3/ECAL/01112023'
config.Data.publication = False
#config.Data.allowNonValidInputDataset = True
config.Data.outputDatasetTag = 'TnP_L1'
config.section_("Site")
config.Site.storageSite = 'T3_CH_CERNBOX'