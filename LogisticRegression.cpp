#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class LogisticRegression
{
public:
    LogisticRegression(vector<vector<double> > &feature_sample,vector<double> &result)
    {
        this->feature_num=feature_sample[0].size()+1;
        cout<<"this->feature_num:"<<this->feature_num<<endl;
        this->sample_num=feature_sample.size();
        for(int i=0;i<sample_num;i++)
        {
            feature_sample[i].insert(feature_sample[i].begin(),1);
        }
        this->feature_sample=feature_sample;
        this->result=result;

        for(int i=0;i<this->sample_num;i++)
        {
            (this->theta).push_back(0);
        }
    }

    double hypothesis(vector<double> &feature_tmp,vector<double> &theta)
    {
        double sum=0.0;
        for(size_t i=0;i<feature_tmp.size();i++)
        {
            sum+=result[i]*feature_tmp[i];
        }
        //cout<<"*******"<<endl;
        return 1/(1+exp(-sum));
    }

    void print_info()
    {
        cout<<"feature_num:"<<feature_num<<endl;
        cout<<"sample_num:"<<sample_num<<endl;

        for(int j=0;j<sample_num;j++)
        {
            cout<<"sample "<<j<<": ";
            for(int i=0;i<feature_num;i++)
                cout<<feature_sample[j][i]<<" ";
            cout<<endl;
        }
        cout<<"result_num:"<<result.size()<<endl;
        cout<<"theta_num:"<<theta.size()<<endl;
    }

    double cost_function()
    {
        double sum=0.0;
        for(size_t i=0;i<result.size();i++)
        {
            sum+=-result[i]*log(hypothesis(feature_sample[i],theta))-(1-result[i])*log(1-hypothesis(feature_sample[i],theta));
        }
        return sum/result.size();
    }

    vector<double> logistic_regression()
    {
        vector<double> delta_w;
        for(int tmp=1;tmp<=iteration;tmp++)
        {
            for(size_t j=0;j<feature_sample[0].size();j++)
            {

                double sum=0.0;
                for(size_t i=0;i<result.size();i++)
                {
                    sum+=(hypothesis(feature_sample[i],theta)-result[i])*feature_sample[i][j];
                }
                delta_w.push_back(sum/result.size()*alpha);
                for(int k=0;k<feature_num;k++)
                {
                    //theta[k]=theta[k]-sum/result.size()*alpha;
                    theta[k]-=delta_w[k];
                }

            }
            //cout<<"cost_funtion:"<<cost_function()<<endl;
        }
        return delta_w;
    }



private:
    vector<vector<double> > feature_sample;
    vector<double> result;
    vector<double> theta;

    int feature_num;
    int sample_num;

    double alpha=0.001;
    int iteration=1500;
};

int main()
{
    vector<vector<double> > ret;
    vector<double> tmp;
    tmp.push_back(1.1);
    //tmp.push_back(1.2);
    //tmp.push_back(1.3);
    ret.push_back(tmp);
    tmp.clear();

    tmp.push_back(1.4);
    //tmp.push_back(1.5);
    //tmp.push_back(1.6);
    ret.push_back(tmp);
    tmp.clear();

    tmp.push_back(1.9);
    ret.push_back(tmp);


    vector<double> res;
    res.push_back(1);
    res.push_back(0);
    res.push_back(1);
    //res.push_back(1);

    LogisticRegression lr(ret,res);
    lr.print_info();
    vector<double> out=lr.logistic_regression();
    cout<<out[0]<<"*****"<<out[1]<<endl;

    cout << "Hello world!" << endl;
    return 0;
}
