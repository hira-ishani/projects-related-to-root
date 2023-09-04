#include "TCanvas.h"
#include "TROOT.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"

using namespace std;

void combine_ISR_Binomial()
{
    gStyle->SetOptFit(1);

    // Data file names for the two datasets
    const char *file1[2] = {"ISR_44", "ppbar_200_ttl"};

    // Range of x-axis for fitting
    const double file2[2] = {2, 2};
    const double file3[2] = {38, 70};

    // Initial parameter values for the Binomial distribution
    const double file4[2] = {0.5, 1.5};
    const double file5[2] = {20, 10};

    char name1[200];
    char name2[200];
    char name3[200];

    for (int i = 0; i < 2; i++) {
        // Format the data file name
        sprintf(name1, "%s.txt", file1[i]);

        // Create a TGraphErrors object and read data from the file
        TGraphErrors graph(name1);

        // Set the graph properties
        graph.SetTitle("Pn vs. n ISR44 and ppbar200 Binomial fits");
        graph.SetMarkerStyle(kOpenCircle);
        graph.SetMarkerColor(kBlue);
        graph.SetLineColor(kBlue);

        // Define the Binomial fit function
        TF1 f("f", "[0]*TMath::Binomial(x, [1]) * TMath::Power([2], x) * TMath::Power((1 - [2]), ([1] - x))", file2[i], file3[i]);

        // Set parameter names and initial values for the Binomial fit
        f.SetParNames("N", "p", "N*p");
        f.SetParameter(0, file4[i]); // N
        f.SetParameter(1, file5[i]); // p
        f.SetParameter(2, file4[i] * file5[i]); // N * p

        // Perform the Binomial fit on the data graph
        graph.Fit(&f, "ME");

        // Create a canvas for plotting
        TCanvas* c1 = new TCanvas();

        // Format the output file name
        sprintf(name3, "PDF-Binomial/%s.pdf", file1[i]);

        // Draw the graph with markers and error bars
        graph.DrawClone("APE");

        // Draw the Binomial fit function on the same canvas
        f.DrawClone("Same");

        // Save the canvas as a PDF file
        c1->SaveAs(name3);

        cout << "" << endl;
        cout << "" << endl;
    }
}

