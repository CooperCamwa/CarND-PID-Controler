#include "PID.h"
#include "math.h"
#include <algorithm>
using namespace std;
/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {
  
}
PID::~PID() {}

void PID::Init(double cp_, double ci_, double cd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  cp=cp_;
  cd=cd_;
  ci=ci_;
  err_p = err_d = err_i = err_avg = total_error = 0;
  //err_d = 0;
  //err_i = 0;
  cp_tw = cd_tw = ci_tw = 0.1;
  counter = dt = 1;
  //cd_tw = 1;
  //ci_tw = 1;
  dp_tw = {cp_tw, cd_tw, ci_tw};
  //err_avg = 0;
  //is_checked = false;
  //counter = 1;
  param_index = 2;
  //dt = 1;
  
  best_error = numeric_limits<double>::max();
  n_settle_steps = 100;
  n_eval_steps = 2000;
  //total_error = 0;
  //tried_adding = false;
  tried_subtracting = tried_adding = false;

}

void PID::UpdateError(double cte) {
  
  err_p = cte;
  if (counter==1){
    err_d = 0;
  } else {
    err_d = (cte - prev_err)/dt;
  }
  err_i += cte * dt;
  prev_err = cte;
  
  if (step % (n_settle_steps + n_eval_steps) > n_settle_steps){
    err_avg += cte*cte;
  }
  
  if ((n_settle_steps + n_eval_steps) == 0){
    err_avg = twiddle(err_avg, counter);
  }
  counter +=1;
  /*
  //if (fabs(cte) > err_max) {
  //      err_max=fabs(cte);
  //}
  err_max = min(err_max, fabs(cte));
  */
}


double PID::err_Total() {
  /**
   * TODO: Calculate and return the total error
   */
  //return err_avg /= counter;  // TODO: Add your total error calc here!
  return 0;
}

double PID::err_Maximum(){
  //return err_max;
}

int PID::Counter(){
  //return counter;
}

double PID::twiddle(double err_avg, int counter) {
  
  if (err_avg < best_error) {
    best_error = err_avg;
    if (counter !=  n_settle_steps + n_eval_steps) {
      dp_tw[param_index] *= 1.1;
    }
    
    param_index = (param_index + 1) % 3;
    tried_adding = tried_subtracting = false;
  }
  
  if (!tried_adding && !tried_subtracting){
    AddToParameterAtIndex(param_index, dp_tw[param_index]);
    tried_adding = true;
  } else if (tried_adding && !tried_subtracting){
    AddToParameterAtIndex(param_index, -2 * dp_tw[param_index]);
    tried_subtracting = true;
  } else {
    AddToParameterAtIndex(param_index, dp_tw[param_index]);
    dp_tw[param_index] *= 0.9;
    param_index = (param_index + 1) % 3;
    tried_adding = tried_subtracting = false;
  }
  err_avg = 0;
  return err_avg;
}

void PID::AddToParameterAtIndex(int index, double p_idx) {
    if (index == 0){
      cp += p_idx;
    }
    else if (index == 1){
      cd += p_idx;
    }
    else if (index == 2){
      ci += p_idx;
    }
}


