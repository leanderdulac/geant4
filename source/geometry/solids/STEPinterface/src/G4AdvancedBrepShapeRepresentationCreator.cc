#include "G4AdvancedBrepShapeRepresentationCreator.hh"
#include<stdio.h>

G4AdvancedBrepShapeRepresentationCreator 
   G4AdvancedBrepShapeRepresentationCreator::csc;


G4AdvancedBrepShapeRepresentationCreator::
   G4AdvancedBrepShapeRepresentationCreator()
{
  G4GeometryTable::RegisterObject(this);
}


G4AdvancedBrepShapeRepresentationCreator::
   ~G4AdvancedBrepShapeRepresentationCreator(){}


void G4AdvancedBrepShapeRepresentationCreator::
   CreateG4Geometry(STEPentity& Ent)
{
  G4String attrName("items");
  STEPattribute *Attr = GetNamedAttribute(attrName, Ent);
  EntityAggregate *ea = (EntityAggregate*)Attr->ptr.a;
  
  // Get parts of this shape  
  G4int partCount = ea->EntryCount();
  EntityNode* en = (EntityNode*)ea->GetHead();

  // An Advaced_BREP_Shape_Representation is made of
  // 0 or 1 G4Axis2Placement3D and 
  // 1 or more Manifold_Solid_BREP 

  G4int placement = 0, nbofsolids = 0;
  G4PlacedSolidVector* placedSldV = new G4PlacedSolidVector(); 
  G4PlacedSolid* placedSld; 
  G4BREPSolid* sld; 
  STEPentity* ent;
  G4Axis2Placement3D* place;

  // default place
  G4Axis2Placement3D* place0 = new (G4Axis2Placement3D)( G4Vector3D(1, 0, 0),
							 G4Vector3D(0, 1, 0),
							 G4Point3D(0, 0, 0)  );
  

  for(G4int a = 0; a < partCount; a++) 
  {
   ent = en->node; 
   void *tmp = G4GeometryTable::CreateObject(*ent); 
    
   if( !strcmp(ent->EntityName(), "Axis2_Placement_3d") )
   {
     // Get placement 
     place = (G4Axis2Placement3D*)tmp;  
     placement = 1;
   }
   else
     if( !strcmp(ent->EntityName(), "Manifold_Solid_Brep") )
     {
       // Get solid    
       sld = (G4BREPSolid*)tmp; 
       nbofsolids++;

       G4int id = ent->GetFileId();
       sld->SetId(id);

       // Create the placed solid 
       if(placement)
	 placedSld = new G4PlacedSolid(sld, place);
       else
	 placedSld = new G4PlacedSolid(sld, place0);
       
       placedSldV->append(placedSld);
     }
   
   en = (EntityNode*)en->NextNode();
  }

  // Get geometric_representation_context, but it is not used
  attrName = "context_of_items";
  Attr = GetNamedAttribute(attrName, Ent);
  
  createdObject = placedSldV;
}


void G4AdvancedBrepShapeRepresentationCreator::CreateSTEPGeometry(void* G4obj)
{

}
