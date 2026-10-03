#include "Cabin.h"
class Cabin : public Housing {
public:
  Cabin::Cabin():Housing(m_location, m_listingStatus){
    m_material = "water";
  }
  Cabin::Cabin(string, string, string):Housing(m_location, m_listingStatus){// Location, Listing Status, and Material
    SetMaterial(material);
  }

  void Cabin::Description(){ // Using m_material, displays Cabin desc
    

  }


  //   to match the sample output
  // Replacing parent class function
  string Cabin::GetMaterial(){     // Getter for m_material
    return m_material;
  }

  void Cabin::SetMaterial(string mat){ // Setter for m_material
    m_material = mat;
  }
