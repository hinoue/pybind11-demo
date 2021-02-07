#include <pybind11/pybind11.h>


int add(int i, int j) {
    return i + j;
}


class Pet
{
    public:
        Pet(const std::string &name, int hunger) : name(name), hunger(hunger) {}
        ~Pet() {}

        void go_for_a_walk() { hunger++; }
        const std::string &get_name() const { return name; }
        int get_hunger() const { return hunger; }

    private:
        std::string name;
        int hunger;
};


namespace py = pybind11;

PYBIND11_MODULE(example, m) {
    // optional module docstring
    m.doc() = "pybind11 example plugin";

    // define add function
    m.def("add", &add, "A function which adds two numbers");

    // bindings to Pet class
    py::class_<Pet>(m, "Pet")
        .def(py::init<const std::string &, int>())
        .def("go_for_a_walk", &Pet::go_for_a_walk)
        .def("get_hunger", &Pet::get_hunger)
        .def("get_name", &Pet::get_name);
}

lvm::Expected<clang::tooling::CommonOptionsParser> create(std::vector<std::string> args, llvm::cl::OptionCategory &optionCategory) {
    // Convert into array that can be manipulated
    int tmp_size = args.size();
    const char** tmp_args = (const char**)malloc(sizeof(char*)*tmp_size);
    for(int i=0; i < tmp_size; i++) {
        tmp_args[i] = args[i].c_str();
    }
    //llvm::Expected<clang::tooling::CommonOptionsParser> ret = clang::tooling::CommonOptionsParser::create(tmp_size, tmp_args, optionCategory, llvm::cl::Optional, NULL);
    llvm::Expected<clang::tooling::CommonOptionsParser> ret = clang::tooling::CommonOptionsParser::create(tmp_size, tmp_args, optionCategory,(llvm::cl::NumOccurrencesFlag)0, NULL);

    // TODO: Empty the array and push it back to args
    return ret;
}


PYBIND11_MODULE(tooling, m) {
    using namespace clang::tooling;
    m.doc() = "pybind11 libtooling plugin";
    py::class_<llvm::cl::OptionCategory>(m, "OptionCategory")
        .def(py::init<const std::string &>());
    py::class_<llvm::Expected<CommonOptionsParser>>(m, "ExpectedCommonOptionsParser");
    py::class_<CommonOptionsParser>(m, "CommonOptionsParser")
        .def("create", (llvm::Expected<CommonOptionsParser> (*) (int &, const char **, llvm::cl::OptionCategory &)) &create);
    //    .def_static("create", py::overload_cast<int &, const char **, llvm::cl::OptionCategory &, llvm::cl::NumOccurrencesFlag, const char *>(&CommonOptionsParser::create));
}
