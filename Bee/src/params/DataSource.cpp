#include "params/DataSource.h"

DataSource::DataSource()
{

}

DataSource::DataSource(std::string sourceNo, std::string sourceName, std::string& hostName, std::string& url)
{

	_sourceNo = sourceNo;
	_sourceName = sourceName;
	_hostName = hostName;
	_url = url;
}

DataSource::~DataSource()
{

}

