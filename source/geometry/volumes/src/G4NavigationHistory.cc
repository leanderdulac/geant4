// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4NavigationHistory.cc,v 1.1.10.1 1999/12/07 20:48:43 gunter Exp $
// GEANT4 tag $Name: geant4-01-00 $
//
// 
// G4NavigationHistory Implementation P.Kent August 96

#include "G4NavigationHistory.hh"
#include "G4ios.hh"

ostream& operator << (ostream& os, const G4NavigationHistory& nav)
{
  G4cout << "History depth="<<nav.GetDepth()<< endl;
  for (G4int i=0;i<=nav.GetDepth();i++)
  {
      os << "Level=["<<i<<"]: " ;
      if( nav.GetVolume(i) != 0 ) {
	 os   << "Phys Name=["<< nav.GetVolume(i)->GetName()
	      << "] Type=[";
	 switch(nav.GetVolumeType(i))
	   {
	   case kNormal:
	     os <<"N";
	     break;
	   case kReplica:
	     os <<"R" << nav.GetReplicaNo(i);
	     break;
	   case kParameterised:
	     os <<"P" << nav.GetReplicaNo(i);
	     break;
	   }
	 os << "]";
      }else{
	 os << "Phys = <Null>";
      }
      os << endl;
  }
  return os;
}
