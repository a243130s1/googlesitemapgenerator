// Copyright 2009 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// SiteManager manages all stuff related to a particular site.
// It controls the lifecycle of site data manager and all services belonging
// to the site.
// It is most widely accessed class in this application. Thread safety is
// carefully ensured to allow maximum efficiency.

#ifndef SITEMAPSERVICE_SITEMANAGER_H__
#define SITEMAPSERVICE_SITEMANAGER_H__

#include <list>

#include "common/sitesetting.h"

#include "sitemapservice/sitedatamanager.h"
#include "sitemapservice/serviceinterface.h"
#include "sitemapservice/servicerunner.h"

class SiteManager {
public:
  SiteManager();
  ~SiteManager();

  const std::string& site_id() const {
    return site_id_;
  }

  // Initialize this manager.
  // "service_queue" is a global queue which contains services from all
  // sites.
  bool Initialize(const std::string& site_id, ServiceQueue* service_queue);

  // Unload this site.
  // Services belonging to this site would be stopped.
  void Unload();

  // Load setting for this site.
  bool Load(const SiteSetting& setting);

  // Process a new url visiting record.
  int ProcessRecord(UrlRecord& record);

  // Schedule services belonging to this site.
  // Ready-to-run service will be put into "service_queue" provided in
  // "Initialize" method above.
  int ScheduleService();

private:
  // A unique site id.
  std::string site_id_;

  SiteDataManager* data_manager_;

  std::list<ServiceInterface*> services_;
  ServiceQueue* service_queue_;

  SiteSetting setting_;
  CriticalSection lock_;
};

#endif // SITEMAPSERVICE_SITEMANAGER_H__
