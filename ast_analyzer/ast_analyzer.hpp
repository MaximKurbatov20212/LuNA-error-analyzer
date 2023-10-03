#include "../parser/ast.hpp"
#include <map>
#include <set>

// std::string to_string() const {
//     std::string p;
//     switch (t) {
//         case INT: return "int";
//         case REAL: return "real";
//         case STRING : return "string";
//         case ERROR_TYPE: return "error_type";
//         case UNDEFINED: return "undefined";
//     }
// }

static std::string print_type(luna_type type) {
    switch (type) {
        case LUNA_INT:  return "int"; 
        case LUNA_REAL:  return "real"; 
        case LUNA_STRING:  return "string"; 
        case LUNA_ERROR_TYPE: return "error_type"; 
        case LUNA_VALUE: return "value"; 
        case LUNA_NAME: return "name"; 
        case LUNA_UNDEFINED: return "undefined"; 
    }
    throw new std::runtime_error("invalid type");
}

class ast_analyzer {
public:
    ast_analyzer(ast* ast, FILE* file) : ast_(ast), file_(file) {}

    ~ast_analyzer() {}

    bool analyze();

private:
    static const int FSEEK_ERROR = -1;
    FILE* file_;
    ast* ast_;

    // bool is_define_in_scope(luna_string* var, std::vector<std::vector<luna_string*>*>* scope);
    // std::vector<luna_string *> get_vars_from_expr(expr* expr);
    // std::vector<luna_string*>* get_vars(std::vector<expr*>* exprs);
    // check_unused(std::vector<std::vector<luna_string*>*>* vars, block* block_);
    bool analyze_unused_variables();
    bool check_unused(std::vector<std::vector<luna_string*>*>* scope, block* block_);

    bool analyze_shadow_import();
    bool have_such_code_id(std::map<std::string, std::string>& map, import* import);
    bool analyze_df_double_declaration();
    bool analyze_existance_main_cf();
    bool analyze_cf_redeclaration();
    bool analyze_df_redeclaration();
    bool has_df_redeclaration(std::vector<luna_string *> prev_values, block* block_);
    bool analyze_calling_undeclarated_func();

    std::multimap<luna_string , std::vector<luna_type> *>* get_types_from_calling(std::multimap<luna_string , std::vector<expr*> *>* cur_cfs);
    std::vector<luna_type>* params_to_types(std::vector<expr *>* params);
    std::multimap<luna_string, std::vector<expr*>*> get_all_calling(block* block);

    std::vector<luna_string *> get_block_values(block* block_);
    std::map<std::string, std::set<uint>> find_redecls(std::vector<luna_string* > values);

    template <typename T>
    std::vector<T> find_pairs(std::vector<T>* v);
    std::string get_line_from_file(uint num);

};