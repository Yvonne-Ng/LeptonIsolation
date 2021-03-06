#
# Basic setup for dumping Tagging information
#

# NOTE: for a real project, you should probably do something more
# complicated. Please follow the SW tutorial if you want to make your
# own package based on this.
#
# https://atlassoftwaredocs.web.cern.ch/ABtutorial/release_setup/


# Set the minimum required CMake version:
cmake_minimum_required( VERSION 3.2 FATAL_ERROR )

# get analysis base
find_package( AnalysisBase 21.2 REQUIRED )

# # Set up a work directory project:
atlas_project( WorkDir 1.0 USE AnalysisBase ${AnalysisBase_VERSION} )


##################################################################
# Package level things
##################################################################
#

# Set the name of the package:
atlas_subdir( LeptonTrackROOTToH5 )

# Packages that this package depends on
atlas_depends_on_subdirs(
  PRIVATE
  Control/xAODRootAccess
  Event/xAOD/xAODTrack
  Event/xAOD/xAODTruth
  Event/xAOD/xAODEgamma
  Event/xAOD/xAODMuon
  PhysicsAnalysis/AnalysisCommon/HDF5Utils
)

# External(s) used by the package:
find_package(ROOT REQUIRED COMPONENTS RIO Hist Tree Net Core)
find_package(HDF5 1.10.1 REQUIRED COMPONENTS CXX C)
find_package(lwtnn)

# common requirements
set(_common
  Root/TrackWriter.cxx
  Root/ElectronWriter.cxx
  Root/MuonWriter.cxx
  INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} ${HDF5_INCLUDE_DIRS} ${LWTNN_INCLUDE_DIRS}
  LINK_LIBRARIES ${ROOT_LIBRARIES} ${HDF5_LIBRARIES} ${LWTNN_LIBRARIES}
  xAODRootAccess
  xAODTracking
  xAODTruth
  xAODEgamma
  xAODMuon
  HDF5Utils
  MuonSelectorToolsLib
  ElectronPhotonSelectorToolsLib
)

# Build the test executable:
atlas_add_executable( dump-xaod util/dump-xaod.cxx ${_common} )

# Set up grid magic. Atlas uses CPack to package up the local files
# and submit them to the grid. If you're not looking to run on the
# grid this is unneeded.
atlas_cpack_setup()
