#include<boost/python.hpp>
#include"database_learning.hpp"

BOOST_PYTHON_MODULE(mass_game_database)
{
	using namespace boost::python;
	using namespace database;
	
	class_<DataBaseLearning>("Learning")
		.def("SetInit", &DataBaseLearning::SetInit)
		.def("SetTerm", &DataBaseLearning::SetTerm)
		.def("PushTurn", &DataBaseLearning::PushTurn)
		.def("PopTurn", &DataBaseLearning::PopTurn)
		.def("Clear", &DataBaseLearning::ClearTurn)
		.def("Save", &DataBaseLearning::Save)
	;
}