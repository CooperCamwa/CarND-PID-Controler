#ifndef PID_H
#define PID_H
#include <vector>
//using namespace std;

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (cp_, ci_, cd_) The initial PID coefficients
   */
  double prev_err;
  double cp;
  double ci;
  double cd;
  double cp_tw;
  double cd_tw;
  double ci_tw;
  
  double err_p;
  double err_i;
  double err_d;
  double dt;
  double err_avg;
  double cte_sqr;
  double err_max;
  bool is_checked;
  int counter;
  int step, param_index;
  std::vector<double> dp_tw;
  std::vector<double> dp;
  int n_settle_steps, n_eval_steps;
  double total_error, best_error;
  bool tried_adding, tried_subtracting, yes_i_wanna_twiddle;
  
  void Init(double cp_, double ci_, double cd_);
  void AddToParameterAtIndex(int index, double amount);
  double twiddle(double err_avg, int counter);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);
  double Steer_Cal(double cte, double speed);
  double err_Total();
  double err_Maximum();
  int Counter();
  
  
  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  

 private:
  /**
   * PID Errors
   */


  /**
   * PID Coefficients
   */ 

};

#endif  // PID_H