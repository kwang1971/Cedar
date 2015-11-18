#include "ob_procedure_stmt.h"
using namespace oceanbase::common;
namespace oceanbase
{
  namespace sql
  {
    void ObProcedureStmt::print(FILE* fp, int32_t level, int32_t index) {
      UNUSED(index);
      print_indentation(fp, level);
      fprintf(fp, "<ObProcedureStmt %d begin>\n", index);
      //print_indentation(fp, level + 1);
      //fprintf(fp, "Expires Count = %d\n",(int32_t)var_val.);
      print_indentation(fp, level);
      fprintf(fp, "<ObProcedureStmt %d End>\n", index);
    }

    int ObProcedureStmt::set_proc_name(const ObString &proc_name)
    {
      proc_name_=proc_name;
      return OB_SUCCESS;
    }

    int ObProcedureStmt::add_proc_param(const ObParamDef &proc_param)
    {
      return params_.push_back(&proc_param);
    }

    int ObProcedureStmt::add_declare_var(const ObString &var)
    {
      int ret=OB_SUCCESS;
      for (int64_t i = 0;i < declare_variable_.count();i++)//判断变量是否重复定义了
      {
        if(declare_variable_.at(i).compare(var)==0)
        {
          TBSYS_LOG(WARN, "same variable");
          ret=-17;
          break;
        }
      }
      if(ret==OB_SUCCESS)
      {
        declare_variable_.push_back(var);
      }
      return ret;
    }

    int ObProcedureStmt::add_stmt(uint64_t& stmt_id)
    {
      return proc_block_.push_back(stmt_id);
    }

    const ObString& ObProcedureStmt::get_proc_name() const
    {
      return proc_name_;
    }

    uint64_t ObProcedureStmt::get_stmt(int64_t index) const
    {
      return proc_block_.at(index);
    }

    const ObString& ObProcedureStmt::get_declare_var(int64_t index) const
    {
      return declare_variable_.at(index);
    }

    int64_t ObProcedureStmt::get_param_size() const
    {
      return params_.count();
    }

    int64_t ObProcedureStmt::get_stmt_size() const
    {
      return proc_block_.count();
    }

    int64_t ObProcedureStmt::get_declare_var_size() const
    {
      return declare_variable_.count();
    }

    const ObArray<ObParamDef>& ObProcedureStmt::get_params() const
    {
      return params_;
    }

    const ObParamDef &ObProcedureStmt::get_param(int64_t index) const
    {
      return params_.at(index);
    }
  }
}



