// SPDX-License-Identifier: GPL-2.0-or-later
// PDX-FileCopyrightText: 2022 Guillaume Frognier <guillaume.frognier@laposte.net>

#include "about.h"

KAboutData AboutType::aboutData() const
{
    return KAboutData::applicationData();
}
