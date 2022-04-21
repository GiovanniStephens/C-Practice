/** This is a simple linear regression program
 * that uses the OLS method to solve for the 
 * coefficients.
 * 
 * Author:  Giovanni Stephens
 * Date:    12/04/2022
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>

class LinearRegressor {
    private:
        std::vector<double> x;
        std::vector<double> y;
        double slope;
        double intercept;
        double r_squared;
        double sse;
        double sst;
        double ssr;
        double mse;
        double rmse;
        double r_squared_adj;
        double f_stat;
        double p_value;
        double t_stat;
        double p_value_t;
        double p_value_f;
        double p_value_r;
        double p_value_r_squared;
        double p_value_r_squared_adj;
        double p_value_mse;
        double p_value_rmse;
        double p_value_sse;
        double p_value_sst;
        double p_value_ssr;
        double p_value_slope;
        double p_value_intercept;
    public:
        LinearRegressor(std::vector<double> x, std::vector<double> y);
        ~LinearRegressor();
        void fit();
        std::map<std::string, double> getStats();
};
