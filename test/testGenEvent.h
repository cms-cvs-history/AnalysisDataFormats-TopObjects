#ifndef testGenEvent_H
#define testGenEvent_H

// system include files
#include <memory>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
#include "FWCore/Framework/interface/EDAnalyzer.h"

using namespace edm;
using namespace std;
//using namespace reco;

#include "TFile.h"
#include "TH1.h"
#include <TTree.h>

class TFile;
class TH1D;
class TTree;

//
// class declaration
//

class testGenEvent : public edm::EDAnalyzer {
 public:
  explicit testGenEvent(const edm::ParameterSet&);
  ~testGenEvent();


 private:
  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  int nevt;
  std::string process;
};
#endif
