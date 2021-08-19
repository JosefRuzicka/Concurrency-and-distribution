//
// Created by charlie on 6/14/21.
//
#include "GoldbachWebApp.hpp"

#include <iostream>
#include <string>

GoldbachWebApp::GoldbachWebApp() {
  // maxCalculators is set to be the amount of processors in the computer.
  this->maxCalculators = std::thread::hardware_concurrency();
  // Create threads (Calculators)
  this->createCalculators();

  // SetUp mathOrderResponseHandler
  this->mathOrderResponseHandler = new GoldbachMathOrderResponseHandler();
  this->mathOrderResponseHandler->setConsumingQueue(&this->processedMathOrders);
  this->mathOrderResponseHandler->startThread();

  // Setup standarResponseHandler

  this->standardResponseHandler = new GoldbachStandardResponseHandler();
  this->standardResponseHandler->setConsumingQueue(&this->standardRequests);
  this->standardResponseHandler->startThread();

  // Setup mathOrderbuilder
  this->mathOrderbuilder = new GoldbachMathOrderBuilder();
  this->mathOrderbuilder->setConsumingQueue(&this->mathRequests);
  this->mathOrderbuilder->setProducingQueue(&this->unprocessedMathOrders);
  this->mathOrderbuilder->startThread();
}

GoldbachWebApp::~GoldbachWebApp() = default;

Queue<HttpRequest> &GoldbachWebApp::getMathRequests() {
  return this->mathRequests;
}

Queue<HttpRequest> &GoldbachWebApp::getStandardRequests() {
  return this->standardRequests;
}

std::string GoldbachWebApp::assemblyHttpResponseBody(
    const std::vector<GoldbachUnit> &goldbachUnits) {
  std::string responseBody;
  {
    for (GoldbachUnit goldbachUnit : goldbachUnits) {
      // Check if goldbach unit is not valid and gives format
      if (!goldbachUnit.isIsValid()) {
        if (goldbachUnit.getDisplaySums()) {
          responseBody.append("-");
        }
        responseBody.append(std::to_string(goldbachUnit.getNumber()));
        responseBody.append(": NA\n");

        // responseBody.append("%zu: NA\n", goldbachUnit.getNumber());
      } else {
        size_t sumsCount = goldbachUnit.getSumsCount();
        if (goldbachUnit.getDisplaySums()) {
          responseBody.append("-");
          responseBody.append(std::to_string(goldbachUnit.getNumber()));
          responseBody.append(": ");
          responseBody.append(std::to_string(goldbachUnit.getSumsCount()));
          responseBody.append(" sums: ");
          size_t indexSuma;

          // Gives format to output if goldbach unit is pair
          if (goldbachUnit.getIsPair()) {
            for (size_t sumCount = 0; sumCount < sumsCount; sumCount++) {
              indexSuma = sumCount * 2;
              responseBody.append(
                  std::to_string(goldbachUnit.getSums()[indexSuma]));
              responseBody.append(" + ");
              responseBody.append(
                  std::to_string(goldbachUnit.getSums()[indexSuma + 1]));

              if (sumCount != (sumsCount - 1)) {
                responseBody.append(", ");
              } else {
                responseBody.append("\n");
              }
            }
          } else {
            // Gives format to output if goldbach unit is odd
            for (size_t sumCount = 0; sumCount < sumsCount; sumCount++) {
              indexSuma = sumCount * 3;

              responseBody.append(
                  std::to_string(goldbachUnit.getSums()[indexSuma]));
              responseBody.append(" + ");

              responseBody.append(
                  std::to_string(goldbachUnit.getSums()[indexSuma + 1]));
              responseBody.append(" + ");
              responseBody.append(
                  std::to_string(goldbachUnit.getSums()[indexSuma + 2]));

              if (sumCount != (sumsCount - 1)) {
                responseBody.append(", ");
              } else {
                responseBody.append("\n");
              }
            }
          }
        } else {
          responseBody.append(std::to_string(goldbachUnit.getNumber()));
          responseBody.append(": ");
          responseBody.append(std::to_string(goldbachUnit.getSumsCount()));
          responseBody.append(" sums");
          responseBody.append(("\n"));
        }
      }
    }
  }
  return responseBody;
}

void GoldbachWebApp::createCalculators() {
  this->calculators.resize(this->maxCalculators);
  for (size_t index = 0; index < maxCalculators; ++index) {
    this->calculators[index] = new GoldbachCalculator();
    this->calculators[index]->setConsumingQueue(&this->unprocessedMathOrders);
    this->calculators[index]->setProducingQueue(&this->processedMathOrders);
    this->calculators[index]->SetIndex(index);

    this->calculators[index]->startThread();

    assert(this->calculators[index]);
  }
}

void GoldbachWebApp::stopCalculators() {
  for (size_t calculator = 0; calculator < this->calculators.size();
       calculator++) {
    this->unprocessedMathOrders.push(GoldbachOrder());
  }
  this->joinCalculators();
}

void GoldbachWebApp::joinCalculators() {
  for (size_t calculator = 0; calculator < this->calculators.size();
       calculator++) {
    this->calculators[calculator]->waitToFinish();
  }
}
