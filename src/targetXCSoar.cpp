//
// This file is part of Condor2Nav file formats translator.
//
// Copyright (C) 2009 Mateusz Pusz
//
// Condor2Nav is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Condor2Nav is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Condor2Nav. If not, see <http://www.gnu.org/licenses/>.
//
// Visit the project webpage (http://sf.net/projects/condor2nav) for more info.
//

/**
 * @file targetXCSoar.cpp
 *
 * @brief Implements the condor2nav::CTargetXCSoar class. 
**/

#include "targetXCSoar.h"


const char *condor2nav::CTargetXCSoar::XCSOAR_PROFILE_NAME    = "xcsoar-registry.prf";


/**
 * @brief Class constructor.
 *
 * condor2nav::CTargetXCSoar class constructor.
 *
 * @param translator Configuration INI file parser.
**/
condor2nav::CTargetXCSoar::CTargetXCSoar(const CTranslator &translator):
CTargetXCSoarCommon(translator),
_profileParser(CTranslator::DATA_PATH + std::string("\\") + XCSOAR_PROFILE_NAME),
_outputXCSoarDataPath(OutputPath() + "\\XCSoarData")
{
  std::string subDir = ConfigParser().Value("XCSoar", "Condor2NavDataSubDir");
  if(subDir != "")
    subDir = "\\" + subDir;
  _outputCondor2NavDataPath = _outputXCSoarDataPath + subDir;
  _condor2navDataPath = ConfigParser().Value("XCSoar", "XCSoarDataPath") + subDir;

  DirectoryCreate(_outputCondor2NavDataPath);

  if(Convert<unsigned>(ConfigParser().Value("XCSoar", "DefaultTaskOverwrite")))
    _outputTaskFilePath = _outputXCSoarDataPath + std::string("\\") + DEFAULT_TASK_FILE_NAME;
  else
    _outputTaskFilePath = _outputCondor2NavDataPath + std::string("\\") + TASK_FILE_NAME;
}


/**
 * @brief Class destructor.
 *
 * condor2nav::CTargetXCSoar class destructor.
**/
condor2nav::CTargetXCSoar::~CTargetXCSoar()
{
  _profileParser.Dump(_outputCondor2NavDataPath + std::string("\\") + OUTPUT_PROFILE_NAME);
}


/**
* @brief Sets scenery map. 
*
* Method sets scenery map XCM data file according to the Condor landscape name. 
*
* @param sceneryData Information describing the scenery. 
**/
void condor2nav::CTargetXCSoar::SceneryMap(const CFileParserCSV::CStringArray &sceneryData)
{
  SceneryMapProcess(_profileParser, sceneryData, _condor2navDataPath);
}


/**
* @brief Sets time for scenery time zone. 
*
* Method sets UTC time offset for selected scenery and forces time synchronization to the GPS source.
**/
void condor2nav::CTargetXCSoar::SceneryTime()
{
  SceneryTimeProcess(_profileParser);
}


/**
* @brief Set glider data. 
*
* Method created and sets glider polar file, handicap, safety speed, the time to empty the water
* ballast and glider name for the logger.
*
* @param gliderData Information describing the glider. 
**/
void condor2nav::CTargetXCSoar::Glider(const CFileParserCSV::CStringArray &gliderData)
{
  GliderProcess(_profileParser, gliderData, _condor2navDataPath, _outputCondor2NavDataPath);
}


/**
* @brief Sets task information. 
*
* Method sets task information.
*
* @param taskParser Condor task parser. 
* @param coordConv  Condor coordinates converter.
**/
void condor2nav::CTargetXCSoar::Task(const CFileParserINI &taskParser, const CCondor::CCoordConverter &coordConv)
{
  TaskProcess(_profileParser, taskParser, coordConv, _outputTaskFilePath);
}
 

/**
* @brief Sets task penalty zones. 
*
* Method sets penalty zones used in the task.
*
* @param taskParser Condor task parser. 
* @param coordConv  Condor coordinates converter.
**/
void condor2nav::CTargetXCSoar::PenaltyZones(const CFileParserINI &taskParser, const CCondor::CCoordConverter &coordConv)
{
  PenaltyZonesProcess(_profileParser, taskParser, coordConv, _condor2navDataPath, _outputCondor2NavDataPath);
}


/**
* @brief Sets weather data. 
*
* Method sets the wind data.
*
* @param taskParser Condor task parser. 
**/
void condor2nav::CTargetXCSoar::Weather(const CFileParserINI &taskParser)
{
  WeatherProcess(_profileParser, taskParser);
}