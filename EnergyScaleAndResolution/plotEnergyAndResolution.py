import ROOT

def read_ttree(file_path, tree_name):


   # Open the ROOT file
   default_file_path = "/eos/user/m/mkovac/Production/RUN_3/ECAL/05122023_CMSSW_13_1_0_pre2/EGamma1/TnP_L1_emulated/231207_174230/0000/"
   emulated_file_path = "/eos/user/m/mkovac/Production/RUN_3/ECAL/05122023_CMSSW_13_1_0_pre2/EGamma1/TnP_L1_emulated_DW_2p5/231205_102116/0000/"
   
   file_default = ROOT.TFile(default_file_path + "TnP_L1_emulated_2023.root", "READ")
   file_emulated = ROOT.TFile(emulated_file_path + "TnP_L1_emulated_DW_2p5_2023.root", "READ")

    # Check if the file is open successfully
   if not (file_default.IsOpen() or file_emulated.IsOpen()):
      print(f"Error: Could not open default or emulated file")
      return
    

   # Get the TTree from the file
   tree_default  = file_default.Get("Ntuplizer/TagAndProbe")
   tree_emulated = file_emulated.Get("Ntuplizer/TagAndProbe")

   # Check if the TTree is found
   if not (tree_default or tree_emulated):
      print(f"Error: TTree TagAndProbe not found in default or emulated file")
      return

   # Get the number of entries in the TTree
   num_entries = tree_default.GetEntries()

   print(f"Number of entries in the default tree: {num_entries}")

   # Loop over entries in the TTree
   for entry in range(num_entries):
      # Load the entry
      tree_default.GetEntry(entry)

      # Access branches and print values
      l1tPt       = tree_default.l1tPt
      EventNumber = tree_default.EventNumber
      allEl_Pt    = tree_default.allEl_Pt

      print(f"Entry {entry}: Branch1 = {l1tPt}")

   # Close the ROOT file
   root_file.Close()


read_ttree("", "")