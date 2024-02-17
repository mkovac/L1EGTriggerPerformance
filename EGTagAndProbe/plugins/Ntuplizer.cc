// system include files
#include <memory>

// User include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/L1Trigger/interface/EGamma.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "L1EGTriggerPerformance/EGTagAndProbe/plugins/tParameterSet.h"

#include "TTree.h"

//#include "FWCore/Framework/interface/ESHandle.h"
//#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
//#include "DataFormats/L1Trigger/interface/EGamma.h"
//#include "DataFormats/VertexReco/interface/Vertex.h"
//#include "DataFormats/Common/interface/ValueMap.h"
//#include "DataFormats/Common/interface/TriggerResults.h"


// Set this variable to decide the number of triggers that you want to check simultaneously
#define NUMBER_OF_MAXIMUM_TRIGGERS 64

using namespace reco;
using namespace edm;
using namespace std;


//======================
// C l a s s
//======================

class Ntuplizer : public edm::one::EDAnalyzer<edm::one::SharedResources, edm::one::WatchRuns>
{
   
   public:
      explicit Ntuplizer(const edm::ParameterSet&);
      ~Ntuplizer() override;
      
      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

      
   private:
      
      void beginJob() override; // Method called once each job just before starting event loop
      void beginRun(edm::Run const&, edm::EventSetup const&) override;
      void analyze(const edm::Event&, const edm::EventSetup&) override;
      void endRun(edm::Run const&, edm::EventSetup const&) override; // Method called once each job just after ending the event loop
      void endJob() override;
   
      void Initialize();
      bool hasFilters(const pat::TriggerObjectStandAlone&  obj , const std::vector<std::string>& filtersToLookFor);
      bool matchToTruth(const edm::Ptr<reco::GsfElectron> ele, const edm::Handle<edm::View<reco::GenParticle>>  &genParticles);


      TTree *_tree;
      TTree *_triggerNamesTreeTag;
      TTree *_triggerNamesTreeProbe;

      TString _treeName, triggerNameTag, triggerNameProbe;
      
      ULong64_t     _indexevents;
      Int_t         _runNumber;
      Int_t         _lumi;
      unsigned long _eleProbeTriggerBits;
      unsigned long _eleTagTriggerBits;


      // All Electrons
      int _allEl_Size;
      vector<float> _allEl_Pt;
      vector<float> _allEl_Eta;
      vector<float> _allEl_Phi;
      vector<float> _allEl_SclEt;
      vector<float> _allEl_Charge;
      vector<float> _allL1tPt;
      vector<float> _allL1tEta;
      vector<float> _allL1tIso;
      vector<float> _allL1tPhi;
      vector<float> _allL1tQual;
       
      // Pantelis offline ID selections
      int _isProbeLoose;
      int _isProbeTight;
      int _isProbeMedium;
      float _Unpacked_dR;
      float _Emulated_dR;
      int _seedTowerEt;
      int _TowerHoE;     
      int _iem;
      int _ihad;
      int _shape;

      float _eleProbePt;
      // std::vector<float> _eleProbePt; 
      float _eleProbeEta;
      // std::vector<float> _eleProbeEta;
      float _eleProbePhi;
      // std::vector<float> _eleProbePhi;
      float _eleProbeSclEt;
      //std::vector<float> _eleProbeSclEt;
      int _eleProbeCharge;
      //std::vector<float> _eleProbeCharge;
      float _hltPt;
      float _hltEta;
      float _hltPhi;
      int _l1tQual;
      float _l1tPt;
      float _l1tEta;
      float _l1tPhi;
      int _l1tIso;
      int _l1tEmuQual;
      float _l1tEmuPt;
      float _l1tEmuEta;
      float _l1tEmuPhi;
      int _l1tEmuIso;
      int _l1tEmuNTT;
      int _l1tEmuTowerIEta;
      int _l1tEmuTowerIPhi;
      int _l1tEmuRawEt;
      int _l1tEmuIsoEt;
      Bool_t _isTagHLTmatched;
      Bool_t _isProbeHLTmatched;
      Bool_t _isOS;
      int _foundTag;
      float _eleTagPt;
      float _eleTagEta;
      float _eleTagPhi;
      int _eleTagCharge;
      float _Mee;
      int _Nvtx;
//      float _dR_histo; // Charis test

      int _hasL1[100];
      int _hasL1_iso[100];

      // Pantelis Emulator
      int _hasL1Emu[100];
      int _hasL1Emu_iso[100];
      int _hasL1_looseiso[100];
      int _hasL1Emu_looseiso[100];
      int _hasL1_tightiso[100];
      int _hasL1Emu_tightiso[100];
          
      edm::EDGetTokenT<edm::View<reco::GsfElectron> >          _electronsTag;
      edm::EDGetTokenT<edm::View<reco::GenParticle> >          _genParticlesTag;
      edm::EDGetTokenT<edm::ValueMap<bool> >                   _eleLooseIdMapTag;
      edm::EDGetTokenT<edm::ValueMap<bool> >                   _eleMediumIdMapTag;
      edm::EDGetTokenT<edm::ValueMap<bool> >                   _eleTightIdMapTag;
      edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> _triggerObjects; // TriggerObjectStandAloneCollection is typedef for std::vector< TriggerObjectStandAlone >
      edm::EDGetTokenT<edm::TriggerResults>                    _triggerBits;
      edm::EDGetTokenT<l1t::EGammaBxCollection>                _L1EGTag;
      edm::EDGetTokenT<l1t::EGammaBxCollection>                _L1EmuEGTag;
      edm::EDGetTokenT<std::vector<reco::Vertex>>              _VtxTag;

      bool _useGenMatch;
      bool _useHLTMatch;

      // !Contains the parameters
      tVParameterSet _parametersTag;
      tVParameterSet _parametersProbe;

      edm::InputTag _processName;
      
      // !Maximum
      std::bitset<NUMBER_OF_MAXIMUM_TRIGGERS> _eleProbeTriggerBitSet;
      std::bitset<NUMBER_OF_MAXIMUM_TRIGGERS> _eleTagTriggerBitSet;

      HLTConfigProvider _hltConfig;
      
      #ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
         edm::ESGetToken<SetupData, SetupRecord> setupToken_;
      #endif

};



//======================
// C o n s t r u c t o r
//======================

Ntuplizer::Ntuplizer(const edm::ParameterSet& iConfig):
   _electronsTag      (consumes<edm::View<reco::GsfElectron> >          (iConfig.getParameter<edm::InputTag>("electrons"))),           // class GsfElectron : public RecoCandidate
   _genParticlesTag   (consumes<edm::View<reco::GenParticle> >          (iConfig.getParameter<edm::InputTag>("genParticles"))),        // class GenParticle
   _eleLooseIdMapTag  (consumes<edm::ValueMap<bool> >                   (iConfig.getParameter<edm::InputTag>("eleLooseIdMap"))),       // class ValueMap
   _eleMediumIdMapTag (consumes<edm::ValueMap<bool> >                   (iConfig.getParameter<edm::InputTag>("eleMediumIdMap"))),      // class ValueMap
   _eleTightIdMapTag  (consumes<edm::ValueMap<bool> >                   (iConfig.getParameter<edm::InputTag>("eleTightIdMap"))),       // class ValueMap
   _triggerObjects    (consumes<pat::TriggerObjectStandAloneCollection> (iConfig.getParameter<edm::InputTag>("triggerSet"))),          // class TriggerObjectStandAlone
   _triggerBits       (consumes<edm::TriggerResults>                    (iConfig.getParameter<edm::InputTag>("triggerResultsLabel"))), // class TriggerResults
   _L1EGTag           (consumes<l1t::EGammaBxCollection>                (iConfig.getParameter<edm::InputTag>("L1EG"))),                // typedef BXVector<EGamma> EGammaBxCollection;
   _L1EmuEGTag        (consumes<l1t::EGammaBxCollection>                (iConfig.getParameter<edm::InputTag>("L1EmuEG"))),             // typedef BXVector<EGamma> EGammaBxCollection;
   _VtxTag            (consumes<std::vector<reco::Vertex>>              (iConfig.getParameter<edm::InputTag>("Vertices")))
{
   _treeName =    iConfig.getParameter<std::string>("treeName");
   _processName = iConfig.getParameter<edm::InputTag>("triggerResultsLabel");
   _useGenMatch = iConfig.getParameter<bool>("useGenMatch");
   _useHLTMatch = iConfig.getParameter<bool>("useHLTMatch");


   #ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
      setupDataToken_ = esConsumes<SetupData, SetupRecord>();
   #endif


   usesResource("TFileService");
   edm::Service<TFileService> fs;
   
   _tree = fs->make<TTree>(_treeName, _treeName); 
   
   _triggerNamesTreeTag   = fs->make<TTree>("triggerNamesTag", "triggerNamesTag");
   _triggerNamesTreeProbe = fs->make<TTree>("triggerNamesProbe", "triggerNamesProbe");
   
   _triggerNamesTreeTag  ->Branch("triggerNamesTag", &triggerNameTag);
   _triggerNamesTreeProbe->Branch("triggerNamesProbe", &triggerNameProbe);
   

   // Building the trigger arrays
   const std::vector<edm::ParameterSet>& HLTListTag = iConfig.getParameter <std::vector<edm::ParameterSet> > ("triggerListTag");
   for (const edm::ParameterSet& parameterSet : HLTListTag)
   {
      tParameterSet pSet;
      pSet.hltPath = parameterSet.getParameter<std::string>("HLT");
      triggerNameTag = pSet.hltPath;
      pSet.hltFilters1 = parameterSet.getParameter<std::vector<std::string> >("path1");
      pSet.hltFilters2 = parameterSet.getParameter<std::vector<std::string> >("path2");
      pSet.leg1 = parameterSet.getParameter<int>("leg1");
      pSet.leg2 = parameterSet.getParameter<int>("leg2");
      _parametersTag.push_back(pSet);
      _triggerNamesTreeTag -> Fill();
      
//      cout << endl << endl << "triggerNameTag = " << triggerNameTag << endl << "hltFilters1 = " << pSet.hltFilters1.at(0) << endl << "hltFilters2 = "
//      << pSet.hltFilters2.at(0) << endl << "leg1 = " << pSet.leg1 << endl << "leg2 = " << pSet.leg2 << endl << endl;
   }




   // Building the trigger arrays
   const std::vector<edm::ParameterSet>& HLTListProbe = iConfig.getParameter <std::vector<edm::ParameterSet> > ("triggerListProbe");
   for (const edm::ParameterSet& parameterSet : HLTListProbe)
   {
      tParameterSet pSet;
      pSet.hltPath = parameterSet.getParameter<std::string>("HLT");
      triggerNameProbe = pSet.hltPath;
      pSet.hltFilters1 = parameterSet.getParameter<std::vector<std::string> >("path1");
      pSet.hltFilters2 = parameterSet.getParameter<std::vector<std::string> >("path2");
      pSet.leg1 = parameterSet.getParameter<int>("leg1");
      pSet.leg2 = parameterSet.getParameter<int>("leg2");
      _parametersProbe.push_back(pSet);
      _triggerNamesTreeProbe -> Fill();
   
//      cout << endl << endl << "triggerNameProbe = " << triggerNameProbe << endl << "hltFilters1 = " << pSet.hltFilters1.at(0) << endl << "hltFilters2 = "
//      << pSet.hltFilters2.at(0) << endl << "leg1 = " << pSet.leg1 << endl << "leg2 = " << pSet.leg2 << endl << endl;
   
   }

   Initialize();
   return;
}
//======================



//======================
// D e s t r u c t o r
//======================

Ntuplizer::~Ntuplizer()
{}
//======================



//==============================================
// b e g i n R u n - checking hltPath existence
//==============================================

void Ntuplizer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
   
//   cout << endl << ">>> beginRun method <<<" << endl;
      
   Bool_t changedConfig = false;

   if(!_hltConfig.init(iRun, iSetup, _processName.process(), changedConfig)){
      edm::LogError("HLTMatchingFilter") << "Initialization of HLTConfigProvider failed!!";
      return;
   }
   
   
   const edm::TriggerNames::Strings& triggerNames = _hltConfig.triggerNames();
   
   
   for (tParameterSet& parameter : _parametersTag)
   {
      const std::string& hltPath = parameter.hltPath;
      bool found = false;
      
      for (unsigned int j = 0; j < triggerNames.size(); j++)
      {
//         cout << triggerNames[j] << std::endl;
         if (triggerNames[j].find(hltPath) != std::string::npos)
         {
            found = true;
            parameter.hltPathIndex = j;

//            cout << "### FOUND AT INDEX #" << j << " --> " << triggerNames[j] << endl;
         }
      }
      if (!found) parameter.hltPathIndex = -1;
   }





   for (tParameterSet& parameter : _parametersProbe)
   {
      const std::string& hltPath = parameter.hltPath;
      bool found = false;
      
      for (unsigned int j = 0; j < triggerNames.size(); j++)
      {
//         cout << triggerNames[j] << std::endl;
         if (triggerNames[j].find(hltPath) != std::string::npos)
         {
            found = true;
            parameter.hltPathIndex = j;

//            cout << "### FOUND AT INDEX #" << j << " --> " << triggerNames[j] << endl;
         }
      }
      if (!found) parameter.hltPathIndex = -1;
   }

}
//======================



//======================
// e n d R u n
//======================

void Ntuplizer::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{}
//======================



//===========================================
// N t u p l i z e r :: I n i t i a l i z e 
//===========================================

void Ntuplizer::Initialize()
{
   
//   cout << endl << ">>> Begin Initialize method <<<" << endl;
   
   _indexevents = 0;
   _runNumber = 0;
   _lumi = 0;
   _eleProbePt = -1.;
   _eleProbeEta = -1.;
   _eleProbePhi = -1.;
   _eleProbeSclEt = -1.;
   _eleProbeCharge = 0;
   _eleTagPt = -1.;
   _eleTagEta = -1.;
   _eleTagPhi = -1.;
   _eleTagCharge = 0;
   _Mee = 0;
   _isTagHLTmatched = false;
   _isProbeHLTmatched = false;
   _hltPt = -1;
   _hltEta = 666;
   _hltPhi = 666;
   _l1tPt = -1;
   _l1tEta = 666;
   _l1tPhi = 666;
   _l1tQual = -1;
   _l1tIso = -1;
   _l1tEmuPt = -1;
   _l1tEmuEta = 666;
   _l1tEmuPhi = 666;
   _l1tEmuQual = -1;
   _l1tEmuIso = -1;
   _l1tEmuNTT = -1;
   _l1tEmuTowerIEta = 666;
   _l1tEmuTowerIPhi = 666;
   _l1tEmuRawEt = -1;
   _l1tEmuIsoEt = -1;
   _foundTag = 0;   
   _allL1tPt.clear();
   _allL1tEta.clear();
   _allL1tPhi.clear();
   _allL1tIso.clear();         
   _allL1tQual.clear();

   _allEl_Size = -1;

   _isProbeLoose = -1;
   _isProbeTight = -1;
   _isProbeMedium = -1;
   
   _Unpacked_dR = -1;
   _Emulated_dR = -1;

   _seedTowerEt = -1;
     
   _TowerHoE = -666;

   _iem = -1;
   _ihad = -1;

   _shape = -2; 


   for( unsigned int i = 0; i < 100; i++ )
   {
      _hasL1[i] = -1;
      _hasL1_iso[i] = -1;
   }

   // Pantelis Emulator
   for( unsigned int i = 0; i < 100; i++)
   {
      _hasL1Emu[i] = -1;
      _hasL1Emu_iso[i] = -1;
      _hasL1_looseiso[i] = -1;
      _hasL1Emu_looseiso[i] = -1;
      _hasL1_tightiso[i] = -1;
      _hasL1Emu_tightiso[i] =-1;
   }

}
//======================








//======================
// b e g i n J o b
//======================

void Ntuplizer::beginJob()
{
   
   cout << endl << ">>> beginJob method <<<" << endl;
      
   //Branches
   _tree -> Branch("EventNumber",&_indexevents,"EventNumber/l");
   _tree -> Branch("RunNumber",&_runNumber,"RunNumber/I");
   _tree -> Branch("lumi",&_lumi,"lumi/I");
   _tree -> Branch("eleProbeTriggerBits", &_eleProbeTriggerBits, "eleProbeTriggerBits/l");
   _tree -> Branch("eleTagTriggerBits", &_eleTagTriggerBits, "eleTagTriggerBits/l");
   _tree -> Branch("eleProbePt",  &_eleProbePt,  "eleProbePt/F");
   _tree -> Branch("eleProbeEta", &_eleProbeEta, "eleProbeEta/F");
   _tree -> Branch("eleProbePhi", &_eleProbePhi, "eleProbePhi/F");
   _tree -> Branch("eleProbeSclEt",  &_eleProbeSclEt,  "eleProbeSclEt/F");
   _tree -> Branch("eleProbeCharge",  &_eleProbeCharge,  "eleProbeCharge/I");
   _tree -> Branch("eleTagPt",  &_eleTagPt,  "eleTagPt/F");
   _tree -> Branch("eleTagEta", &_eleTagEta, "eleTagEta/F");
   _tree -> Branch("eleTagPhi", &_eleTagPhi, "eleTagPhi/F");
   _tree -> Branch("eleTagCharge",  &_eleTagCharge,  "eleTagCharge/I");
   _tree -> Branch("Mee",  &_Mee,  "Mee/F");
   _tree -> Branch("hltPt",  &_hltPt,  "hltPt/F");
   _tree -> Branch("hltEta", &_hltEta, "hltEta/F");
   _tree -> Branch("hltPhi", &_hltPhi, "hltPhi/F");
   _tree -> Branch("l1tPt",  &_l1tPt,  "l1tPt/F");
   _tree -> Branch("l1tEta", &_l1tEta, "l1tEta/F");
   _tree -> Branch("l1tPhi", &_l1tPhi, "l1tPhi/F");
   _tree -> Branch("l1tQual", &_l1tQual, "l1tQual/I");
   _tree -> Branch("l1tIso", &_l1tIso, "l1tIso/I");
   _tree -> Branch("l1tEmuPt",  &_l1tEmuPt,  "l1tEmuPt/F");
   _tree -> Branch("l1tEmuEta", &_l1tEmuEta, "l1tEmuEta/F");
   _tree -> Branch("l1tEmuPhi", &_l1tEmuPhi, "l1tEmuPhi/F");
   _tree -> Branch("l1tEmuQual", &_l1tEmuQual, "l1tEmuQual/I");
   _tree -> Branch("l1tEmuIso", &_l1tEmuIso, "l1tEmuIso/I");
   _tree -> Branch("l1tEmuNTT", &_l1tEmuNTT, "l1tEmuNTT/I");
   _tree -> Branch("l1tEmuTowerIEta", &_l1tEmuTowerIEta, "l1tEmuTowerIEta/I");
   _tree -> Branch("l1tEmuTowerIPhi", &_l1tEmuTowerIPhi, "l1tEmuTowerIPhi/I");
   _tree -> Branch("l1tEmuRawEt", &_l1tEmuRawEt, "l1tEmuRawEt/I");
   _tree -> Branch("l1tEmuIsoEt", &_l1tEmuIsoEt, "l1tEmuIsoEt/I");
        
   ////////////////////////////////// Pantelis offlineIDs Branches ///////////////////////////
   _tree -> Branch("isProbeLoose", &_isProbeLoose, "isProbeLoose/I");
   _tree -> Branch("isProbeTight", &_isProbeTight, "isProbeTight/I");
   _tree -> Branch("isProbeMedium", &_isProbeMedium, "isProbeMedium/I");
   _tree -> Branch("UnpackedDR", &_Unpacked_dR, "UnpackedDR/F");
   _tree -> Branch("EmulatedDR", &_Emulated_dR, "EmulatedDR/F");
   _tree -> Branch("seedTowerEt", &_seedTowerEt, "seedTowerEt/I");
   _tree -> Branch("TowerHoE", &_TowerHoE,"TowerHoE/I");
   _tree -> Branch("iem", &_iem,"iem/I");
   _tree -> Branch("ihad", &_ihad,"ihad/I");
   _tree -> Branch("shape", &_shape, "shape/I");
   ///////////////////////////////////////////////////////////////////////////////////////////  
         
   ///////////////////////////////All Electrons////////////////////////////////////////////////
   _tree -> Branch("allEl_Pt", &_allEl_Pt);//, "allElectonsPt/array");
   _tree -> Branch("allEl_Eta", &_allEl_Eta);//, "allElectonsEta/array");
   _tree -> Branch("allEl_Phi", &_allEl_Phi);//, "allElectonsPhi/array");
   _tree -> Branch("allEl_SclEt", &_allEl_SclEt);//, "allElectonsSclEt/array");
   _tree -> Branch("allEl_Charge", &_allEl_Charge);//, "allElectonsCharge/array");
   _tree -> Branch("allEl_Size", &_allEl_Size, "allEl_Size/I");

   _tree -> Branch("allL1tPt", &_allL1tPt);
   _tree -> Branch("allL1tEta", &_allL1tEta);
   _tree -> Branch("allL1tPhi", &_allL1tPhi);
   _tree -> Branch("allL1tIso", &_allL1tIso);
   _tree -> Branch("allL1tQual", &_allL1tQual);  
   ///////////////////////////////////////////////////////////////////////////////////////

   _tree -> Branch("isTagHLTmatched", &_isTagHLTmatched, "isTagHLTmatched/O");
   _tree -> Branch("isProbeHLTmatched", &_isProbeHLTmatched, "isProbeHLTmatched/O");
   _tree -> Branch("isOS", &_isOS, "isOS/O");
   _tree -> Branch("foundTag", &_foundTag, "foundTag/I");
   _tree -> Branch("Nvtx", &_Nvtx, "Nvtx/I");

//   _tree -> Branch("dR_histo", &_dR_histo,"dR_histo/F"); //Charis test Dr



   for( unsigned int i = 0; i < 100; i++ )
   {  
      TString name = Form("hasL1_%i", i);
      _tree -> Branch(name,  &_hasL1[i],  name+"/I");
      
      TString name_iso = Form("hasL1_iso_%i",i);
      _tree -> Branch(name_iso,  &_hasL1_iso[i],  name_iso+"/I");
      
      TString name_looseiso = Form("hasL1_looseiso_%i",i);
      _tree -> Branch(name_looseiso,  &_hasL1_looseiso[i],  name_looseiso+"/I");
      
      TString name_tightiso = Form("hasL1_tightiso_%i",i);
      _tree -> Branch(name_tightiso,  &_hasL1_tightiso[i],  name_tightiso+"/I");


   }
        
   /////////////////////////////// Pantelis Emulator /////////////////////////
   for( unsigned int i = 0; i < 100; i++ )
   {
      TString name = Form("hasL1Emu_%i",i);
      _tree -> Branch(name, &_hasL1Emu[i], name+"/I");
      
      TString name_iso = Form("hasL1Emu_iso%i",i);
      _tree -> Branch(name_iso, &_hasL1Emu_iso[i], name_iso+"/I");
      
      TString name_looseiso = Form("hasL1Emu_looseiso%i",i);
      _tree -> Branch(name_looseiso, &_hasL1Emu_looseiso[i], name_looseiso+"/I"); 
      
      TString name_tightiso = Form("hasL1Emu_tightiso%i",i);
      _tree -> Branch(name_tightiso, &_hasL1Emu_tightiso[i], name_tightiso+"/I");
   }  
        
   //////////////////////////////////////////////////////////////////////////

   return;
}
//======================



//======================
// e n d J o b
//======================

void Ntuplizer::endJob()
{}
//======================



//======================
// a n a l y z e
//======================

void Ntuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& eSetup)
{
   
//   cout << endl << ">>> Begin analyze method <<<" << endl;
   
   // Search for the tag in the event
   edm::Handle<edm::View<reco::GsfElectron> >          electrons;
   edm::Handle<edm::View<reco::GenParticle> >          genParticles;
   edm::Handle<edm::ValueMap<bool> >                   loose_id_decisions;
   edm::Handle<edm::ValueMap<bool> >                   medium_id_decisions;
   edm::Handle<edm::ValueMap<bool> >                   tight_id_decisions; // Pantelis TightIDs
   edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
   edm::Handle<edm::TriggerResults>                    triggerBits;
   edm::Handle<std::vector<reco::Vertex> >             vertices;

   iEvent.getByToken(_electronsTag, electrons);
   iEvent.getByToken(_eleLooseIdMapTag,  loose_id_decisions);
   iEvent.getByToken(_eleMediumIdMapTag, medium_id_decisions);
   iEvent.getByToken(_eleTightIdMapTag,  tight_id_decisions); // Pantelis TightIDs
   
   if (_useHLTMatch)
      iEvent.getByToken(_triggerObjects, triggerObjects);
   
   iEvent.getByToken(_triggerBits, triggerBits);
   iEvent.getByToken(_VtxTag, vertices);

   if (_useGenMatch)
      iEvent.getByToken(_genParticlesTag, genParticles);


   const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);


   _allEl_Pt.clear();
   _allEl_Eta.clear();
   _allEl_Phi.clear();
   _allEl_SclEt.clear();
   _allEl_Charge.clear();

   _allEl_Size = electrons->size();      


   for (unsigned int k = 0; k < electrons->size(); ++k)
   {
      const auto ele = electrons->ptrAt(k);
      _allEl_Pt.push_back(ele->pt());
      _allEl_Eta.push_back(ele->eta());
      _allEl_Phi.push_back(ele->phi());
      _allEl_SclEt.push_back((ele->superCluster()->energy()) / cosh(ele->superCluster()->eta()));
      _allEl_Charge.push_back(ele->charge());
      
   }

   // Start tag loop
   for (unsigned int i = 0; i< electrons->size(); ++i)
   {
      const auto eleTag = electrons->ptrAt(i);
      int isTagIDMedium = (*medium_id_decisions)[eleTag];
      if (!isTagIDMedium || eleTag->p4().Pt()<30) continue;

      // Start probe loop
      for (unsigned int j = 0; j< electrons->size(); ++j)
      {
         if (i==j) continue;   
                                               
         Initialize();
         _indexevents = iEvent.id().event();
         _runNumber = iEvent.id().run();
         _lumi = iEvent.luminosityBlock();
  
         const auto eleProbe = electrons->ptrAt(j);
         
         // int isProbeLoose = (*loose_id_decisions)[eleProbe];
         int isProbeLoose2 = (*loose_id_decisions)[eleProbe];
         int isProbeTight = (*tight_id_decisions)[eleProbe];
         int isProbeMedium =(*medium_id_decisions)[eleProbe];
         _isProbeLoose = isProbeLoose2;
         _isProbeTight = isProbeTight;
         _isProbeMedium = isProbeMedium;

         float eleProbeEta = eleProbe->p4().Eta();
         if ((abs(eleProbeEta) > 1.4442 && abs(eleProbeEta) < 1.566)) continue; // Skip crack electrons

         bool isOS = (eleTag->charge()/eleProbe->charge() < 0) ? true : false;
         if(!isOS) continue;

         float Mee = (eleTag->p4() + eleProbe->p4()).M();
         if (!(Mee > 60 && Mee < 120)) continue;

         if (_useGenMatch)
         {
            if (!matchToTruth(eleProbe, genParticles))
               continue;
         }

         _isOS = isOS;
         _Mee = Mee;

//         cout << endl << "iEvent.id().event() = " << iEvent.id().event() << endl << "_allEl_Size = " << electrons->size() << endl;
//         cout << endl << "TAG index = " << i << endl << "PROBE index = " << j << endl;




         //=======================   
         // TagAndProbe on HLT EG
         //=======================   
         
         _eleProbeTriggerBitSet.reset();
         _eleTagTriggerBitSet.reset();

         if (_useHLTMatch)
         {
            for (pat::TriggerObjectStandAlone obj : *triggerObjects) // Iterate over triggerObjects vector which is a vector of TriggerObjectStandAlone class objects
            {
               if (!obj.hasCollection("hltEgammaCandidates::HLT")) continue;
               
               const float dR_tag = deltaR (*eleTag, obj);
               if (dR_tag < 0.3)
               {        
                  obj.unpackPathNames(names);
                  
                  const edm::TriggerNames::Strings& triggerNames = names.triggerNames();

                  // Looking for the path
                  unsigned int x = 0;
                  bool foundTrigger = false;   

                  for (const tParameterSet& parameter : _parametersTag)
                  {
                     if ((parameter.hltPathIndex >= 0) && (obj.hasPathName(triggerNames[parameter.hltPathIndex], true, false)))
                     {
                        foundTrigger = true;
                        //Path found, now looking for the label 1, if present in the parameter set
//                        std::cout << "==== FOUND PATH " << triggerNames[parameter.hltPathIndex] << " ====" << std::endl;
                        //Retrieving filter list for the event
                        const std::vector<std::string>& filters = (parameter.hltFilters1);
                        if (hasFilters(obj, filters))
                        {
//                           std::cout << "#### FOUND ELE WITH HLT PATH " << x << " ####" << std::endl;
                           _hltPt = obj.pt();
                           _hltEta = obj.eta();
                           _hltPhi = obj.phi();
                           _eleTagTriggerBitSet[x] = true;             
//                           std::cout << _eleTagTriggerBitSet.to_string() << std::endl;
                        }
                     }
                     x++;
                  }
                  if (foundTrigger)
                  {
                     _isTagHLTmatched = true;
                     _foundTag++;
                  }
               }// end if dR_tag


               const float dR_probe = deltaR (*eleProbe, obj);
               if (dR_probe < 0.3)
               {
                  _isProbeHLTmatched = true;

                  obj.unpackPathNames(names);
                  const edm::TriggerNames::Strings& triggerNames = names.triggerNames();
                  
                  // Looking for the path
                  unsigned int x = 0;
                  bool foundTrigger = false;
                  
                  for (const tParameterSet& parameter : _parametersProbe)
                  {
                     if ((parameter.hltPathIndex >= 0) && (obj.hasPathName(triggerNames[parameter.hltPathIndex], true, false)))
                     {
                        foundTrigger = true;           
                        const std::vector<std::string>& filters = (parameter.hltFilters1);
                        if (hasFilters(obj, filters))
                        {
//                           std::cout << "#### FOUND ELE WITH HLT PATH " << x << " ####" << std::endl;
                           _hltPt = obj.pt();
                           _hltEta = obj.eta();
                           _hltPhi = obj.phi();
                           _eleProbeTriggerBitSet[x] = true;
                        }
                     }
                     x++;
                  }
                  if (foundTrigger)
                  {
                     _isProbeHLTmatched = true;
                  }
               } // end if dR_probe
               
            } // end iteration over triggerObjects
            if(!(_isTagHLTmatched)) continue;
         } // end if _useHLTMatch






         //=======================
         // TagAndProbe on L1T EG
         //=======================
         
         edm::Handle<BXVector<l1t::EGamma>> L1EGHandle;
         iEvent.getByToken(_L1EGTag, L1EGHandle);

         float minDR = 0.3; // Uncomment for new match algo; Charis test
         
         _allL1tPt.clear();
         _allL1tEta.clear();
         _allL1tPhi.clear();
         _allL1tIso.clear();
         _allL1tQual.clear();

         for (l1t::EGammaBxCollection::const_iterator bx0EGIt = L1EGHandle->begin(0); bx0EGIt != L1EGHandle->end(0); bx0EGIt++)
         {    
            const l1t::EGamma &l1tEG = *bx0EGIt;                            
            _allL1tPt.push_back(l1tEG.pt());
            _allL1tEta.push_back(l1tEG.eta());
            _allL1tPhi.push_back(l1tEG.phi());
            _allL1tIso.push_back(l1tEG.hwIso());
            _allL1tQual.push_back(l1tEG.hwQual());
         }


         for (l1t::EGammaBxCollection::const_iterator bx0EGIt = L1EGHandle->begin(0); bx0EGIt != L1EGHandle->end(0); bx0EGIt++)
         {
            const float dR = deltaR(*eleProbe, *bx0EGIt);
            _Unpacked_dR = dR;
                             
            const l1t::EGamma &l1tEG = *bx0EGIt;

//            cout << "FW EG, pT = "<<l1tEG.pt()<<", eta = "<<l1tEG.eta()<<", phi = "<<l1tEG.phi()<<endl;

            if (dR < minDR) // Uncomment for new match algo
            {
               minDR = dR; // Uncomment for new match algo
               _l1tPt = l1tEG.pt();
               _l1tEta = l1tEG.eta();
               _l1tPhi = l1tEG.phi();
               _l1tIso = l1tEG.hwIso();
               _l1tQual = l1tEG.hwQual();
            }
            
//            _dR_histo = minDR; //Charis test 
         } // end for EGammaBxCollection


         for (unsigned int i = 0; i < 100; i++)
         {
            _hasL1[i]          = (_l1tPt) >= i;
            _hasL1_iso[i]      = ((_l1tIso) && (_l1tPt) >= i);
            _hasL1_looseiso[i] = (((_l1tIso) == 2 || (_l1tIso) == 3) && (_l1tPt) >= i);
            _hasL1_tightiso[i] = (((_l1tIso) == 1 || (_l1tIso) == 3) && (_l1tPt) >= i);

         }


         edm::Handle<BXVector<l1t::EGamma>> L1EmuEGHandle;
         try
         {
            iEvent.getByToken(_L1EmuEGTag, L1EmuEGHandle);
         }
         catch (...)
         {;}

         if (L1EmuEGHandle.isValid())
         {
            minDR = 0.3;

            for (l1t::EGammaBxCollection::const_iterator bx0EmuEGIt = L1EmuEGHandle->begin(0); bx0EmuEGIt != L1EmuEGHandle->end(0) ; bx0EmuEGIt++)
            {
               const float dR = deltaR(*eleProbe, *bx0EmuEGIt);
               _Emulated_dR = dR;
               const l1t::EGamma &l1tEmuEG = *bx0EmuEGIt;
                 
               if (dR < minDR) // Uncomment for new match algo
               {
                  minDR = dR; // Uncomment for new match algo
                  _l1tEmuPt        = l1tEmuEG.pt();
                  _l1tEmuEta       = l1tEmuEG.eta();
                  _l1tEmuPhi       = l1tEmuEG.phi();
                  _l1tEmuIso       = l1tEmuEG.hwIso();
                  _l1tEmuNTT       = l1tEmuEG.nTT();
                  _l1tEmuQual      = l1tEmuEG.hwQual();
                  _l1tEmuTowerIEta = l1tEmuEG.towerIEta();
                  _l1tEmuTowerIPhi = l1tEmuEG.towerIPhi();
                  _l1tEmuRawEt     = l1tEmuEG.rawEt();
                  _l1tEmuIsoEt     = l1tEmuEG.isoEt();
//                  _seedTowerEt     = l1tEmuEG.seedTowerEt(); 
                   _TowerHoE       = l1tEmuEG.towerHoE();  
//                  _iem             = l1tEmuEG.seedTowerEm();
//                  _ihad            = l1tEmuEG.seedTowerHad();
                  _shape           = l1tEmuEG.shape();
               } // end if
            } // end for EGammaBxCollection
                      
            ///////////////////////// Pantelis Emulator ////////////////////////////////////////
            for (unsigned int i = 0; i < 100; i++)
            {
               _hasL1Emu[i]          = (_l1tEmuPt) >= i;
               _hasL1Emu_iso[i]      = ((_l1tEmuIso) && ( _l1tEmuPt) >=i );
               _hasL1Emu_looseiso[i] = (((_l1tEmuIso)==2 || (_l1tEmuIso)==3) && (_l1tEmuPt)>=i);
               _hasL1Emu_tightiso[i] = (((_l1tEmuIso)==1 || (_l1tEmuIso)==3) && (_l1tEmuPt)>=i);
            } 
            ////////////////////////////////////////////////////////////////////////////////////
                        
         } // end if L1EmuEGHandle.isValid()

         _eleProbePt = eleProbe->pt();
         _eleProbeEta = eleProbe->eta();
         _eleProbePhi = eleProbe->phi();
         _eleProbeSclEt = (eleProbe->superCluster()->energy()) / cosh(eleProbe->superCluster()->eta()) ;
         _eleProbeCharge = eleProbe->charge();


         _eleTagPt = eleTag->pt();
         _eleTagEta = eleTag->eta();
         _eleTagPhi = eleTag->phi();
         _eleTagCharge = eleTag->charge();

         _Nvtx = vertices->size();

         _eleProbeTriggerBits = _eleProbeTriggerBitSet.to_ulong();
         _eleTagTriggerBits = _eleTagTriggerBitSet.to_ulong();

         _tree -> Fill();

      } // end probe loop
   } // end tag loop



#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  // if the SetupData is always needed
  auto setup = iSetup.getData(setupToken_);
  // if need the ESHandle to check if the SetupData was there or not
  auto pSetup = iSetup.getHandle(setupToken_);
#endif

}
//======================



//======================
// hasFilters
//======================

bool Ntuplizer::hasFilters(const pat::TriggerObjectStandAlone&  obj , const std::vector<std::string>& filtersToLookFor) {

   const std::vector<std::string>& eventLabels = obj.filterLabels();
   for (const std::string& filter : filtersToLookFor)
   {
      //Looking for matching filters
      bool found = false;
      for (const std::string& label : eventLabels)
      {
         //if (label == std::string("hltOverlapFilterIsoMu17MediumIsoPFTau40Reg"))
         if (label == filter)
         {

//            std::cout << "#### FOUND FILTER " << label << " == " << filter << " ####" << std::endl;
            found = true;
         }
      }
      if(!found) return false;
   }

   return true;
}
//======================



//======================
// matchToTruth
//======================

bool Ntuplizer::matchToTruth(const edm::Ptr<reco::GsfElectron> ele, 
      const edm::Handle<edm::View<reco::GenParticle>> &prunedGenParticles){

   // 
   // Explicit loop and geometric matching method
   //

   // Find the closest status 1 gen electron to the reco electron
   double dR = 999;
   const reco::Candidate *closestElectron = 0;
   for(size_t i=0; i<prunedGenParticles->size();i++){
      const reco::Candidate *particle = &(*prunedGenParticles)[i];
      // Drop everything that is not electron or not status 1
      if( abs(particle->pdgId()) != 11 || particle->status() != 1 || particle->pt()<5)
         continue;
      //
      double dRtmp = deltaR( ele->p4(), particle->p4() );
      if( dRtmp < dR ){
         dR = dRtmp;
         closestElectron = particle;
      }
   }
   // See if the closest electron (if it exists) is close enough.
   // If not, no match found.
   if( !(closestElectron != 0 && dR < 0.1) ) {
      return false;
   }

   return true;
}
//======================



// Method fills 'descriptions' with the allowed parameters for the module
void Ntuplizer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  // The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addWithDefaultLabel(desc);
}


//define this as a plug-in
DEFINE_FWK_MODULE(Ntuplizer);