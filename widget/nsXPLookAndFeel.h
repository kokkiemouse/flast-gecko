/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __nsXPLookAndFeel
#define __nsXPLookAndFeel

#include "mozilla/LookAndFeel.h"
#include "mozilla/widget/LookAndFeelTypes.h"
#include "nsTArray.h"

class nsLookAndFeel;

class nsXPLookAndFeel : public mozilla::LookAndFeel {
 public:
  virtual ~nsXPLookAndFeel();

  static nsXPLookAndFeel* GetInstance();
  static void Shutdown();

  void Init();

  // These functions will return a value specified by an override pref, if it
  // exists, and otherwise will call into the NativeGetXxx function to get the
  // platform-specific value.
  //
  // NS_ERROR_NOT_AVAILABLE is returned if there is neither an override pref or
  // a platform-specific value.
  nsresult GetColorValue(ColorID aID, bool aUseStandinsForNativeColors,
                         nscolor& aResult);
  nsresult GetIntValue(IntID aID, int32_t& aResult);
  nsresult GetFloatValue(FloatID aID, float& aResult);
  // Same, but returns false if there is no platform-specific value.
  // (There are no override prefs for font values.)
  bool GetFontValue(FontID aID, nsString& aName, gfxFontStyle& aStyle) {
    return NativeGetFont(aID, aName, aStyle);
  }

  virtual nsresult NativeGetInt(IntID aID, int32_t& aResult) = 0;
  virtual nsresult NativeGetFloat(FloatID aID, float& aResult) = 0;
  virtual nsresult NativeGetColor(ColorID aID, nscolor& aResult) = 0;
  virtual bool NativeGetFont(FontID aID, nsString& aName,
                             gfxFontStyle& aStyle) = 0;

  virtual void RefreshImpl();

  virtual char16_t GetPasswordCharacterImpl() { return char16_t('*'); }

  virtual bool GetEchoPasswordImpl() { return false; }

  virtual uint32_t GetPasswordMaskDelayImpl() { return 600; }

  using FullLookAndFeel = mozilla::widget::FullLookAndFeel;
  using LookAndFeelCache = mozilla::widget::LookAndFeelCache;
  using LookAndFeelInt = mozilla::widget::LookAndFeelInt;
  using LookAndFeelFont = mozilla::widget::LookAndFeelFont;
  using LookAndFeelColor = mozilla::widget::LookAndFeelColor;
  using LookAndFeelTheme = mozilla::widget::LookAndFeelTheme;

  virtual LookAndFeelCache GetCacheImpl();
  virtual void SetCacheImpl(const LookAndFeelCache& aCache) {}
  virtual void SetDataImpl(FullLookAndFeel&& aTables) {}

  virtual void NativeInit() = 0;

  virtual void WithThemeConfiguredForContent(
      const std::function<void(const LookAndFeelTheme& aTheme)>& aFn) {
    aFn(LookAndFeelTheme{});
  }

 protected:
  nsXPLookAndFeel() = default;

  static nscolor GetStandinForNativeColor(ColorID);
  void RecordTelemetry();
  virtual void RecordLookAndFeelSpecificTelemetry() {}

  static void OnPrefChanged(const char* aPref, void* aClosure);

  static bool sInitialized;

  static nsXPLookAndFeel* sInstance;
  static bool sShutdown;
};

#endif
