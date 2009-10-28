//
// This file is a part of Condor2Nav file formats translator.
//
// Copyright (C) 2009 Mateusz Pusz
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Visit the project webpage (http://sf.net/projects/condor2nav) for more info.
//

#include "translator.h"
#include "tools.h"


condor2nav::CTranslator::CTranslator(const std::string &outputPath):
_outputPath(outputPath)
{
  DirectoryCreate(_outputPath);
}


condor2nav::CTranslator::~CTranslator()
{
}


const std::string &condor2nav::CTranslator::OutputPath() const
{
  return _outputPath;
}
