#include <gmsh.h>
#include <set>
int main(int argc, char **argv) {
    gmsh::initialize();

    const double R = 10.0;  
    const double ext_r = 3.0;
    const double int_r = 2.0; 

    gmsh::model::add("tokamak");

    int tag_ext = 1, tag_int = 2;
    gmsh::model::occ::addTorus(R, 0, 0, R, ext_r, tag_ext);
    gmsh::model::occ::addTorus(R, 0, 0, R, int_r, tag_int);
    const double thickness = ext_r - int_r;
    
    std::vector<std::pair<int, int>> out;
    std::vector<std::vector<std::pair<int, int>>> outmap;
    gmsh::model::occ::cut({{3, tag_ext}}, {{3, tag_int}}, out, outmap);
    gmsh::model::occ::synchronize();


    const double elem_size = thickness/4.0;
    gmsh::option::setNumber("Mesh.CharacteristicLengthMin", elem_size);
    gmsh::option::setNumber("Mesh.CharacteristicLengthMax", elem_size);

    gmsh::option::setNumber("Mesh.Algorithm3D", 1); 

    gmsh::model::mesh::generate(3);
    gmsh::write("tokamak.msh");
        
    std::set<std::string> args(argv, argv + argc);
    if(!args.count("-nopopup")) gmsh::fltk::run();


  
    gmsh::finalize();
  
    return 0;
  }
