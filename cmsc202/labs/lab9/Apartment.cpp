#include "Apartment.h"

Apartment(); // Default constructor and calls RandLayout
Apartment(string, string); //Location, Listing Status and calls RandLayout
void RandLayout();       // Randomly assigns one LAYOUT to m_layout
string GetLayout();      // Getter for m_layout (extending parent)
void SetLayout(string);  // Setter for m_layout (extending parent)
void Visit();
