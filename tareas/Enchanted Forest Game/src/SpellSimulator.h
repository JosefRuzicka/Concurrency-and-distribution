/**
 * Spell Simulator class. used by the Wizard to check if any spells must be cast
 * on the forest and update it accordingly.
 * Programmed by Josef Ruzicka, Samantha Romero and Carlos Solorzano.
 */

#ifndef _SPELLSIMULATOR_H
#define _SPELLSIMULATOR_H

#include <fstream>
#include <iostream>

#include "Forest.h"
class SpellSimulator {
 public:
  /**
   * @brief: call the cell updater for every cell every night and append the
   * resulting forest to the forest string. uses a temporary matrix to update
   * cells without loosing track of the original forest.
   * @param originalForestName: original forest name
   * @param originalForest: the forest as it was by the start ot the midnight.
   * @param newForest: the resulting forest after the midnight.
   * @param saveAllMaps: bool value determinating wheter or not the forest
   * should be printed after every midnight
   * @param nights: the amount of midnights that should be run by the
   * simulation.
   */
  void updateForest(std::string originalForestName, Forest* originalForest,
                    Forest* newForest, bool saveAllMaps, int nights,
                    std::ofstream* archivoSalida);

 private:
  /**
   * @brief: checks if any of the land-transforming rules apply to the cell at
   * matriz[row][column].
   * @param originalForest: the forest as it was by the start ot the midnight.
   * @param newForest: the resulting forest after the midnight.
   * @param row
   * @param column
   */
  void transformCell(Forest* originalForest, Forest* newForest, int row,
                     int column);
  /**
   * @brief: appends the current forest to the forests string to be written on
   * the output file.
   * @param night: current night of the simulation.
   * @param mapFile: the file to be written on.
   * @param originalMapName: the name of the input map file.
   * @param forests: the string of forests to be written on the output file.
   */
  int saveForestOnTxt(int night, std::ofstream* mapFile,
                      std::string originalMapName, std::string forests);

  /**
   * @brief: defines a new name for the file.
   * @param currentNight: the night that must be appended to the file name.
   * @param fileName: the original input file name.
   */
  std::string obtainNewName(int currentNight, std::string fileName);
   /**
   * @brief: checks if the cell should be transformed.
   * @param originalForest: the forest as it was by the start ot the midnight.
   * @param row
   * @param column
   * @param myValue: current cell value.
   * @param ruleValue: value evaluated by rule.
   */
  bool checkTransformation(Forest* originalForest, int row, int column,
                           char myValue, char ruleValue);
};

#endif  //_SPELLSIMULATOR_H