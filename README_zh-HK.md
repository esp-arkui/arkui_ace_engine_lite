# JS-UI框架子系統組件<a name="ZH-CN_TOPIC_0000001125689015"></a>
- [簡介]（#section11660541593）
- [目錄]（#section1464106163817）
- [介面]（#section1096322014288）
- [使用]（#section1529834174016）
- [相關倉]（#section11683135113011）
##簡介<a name="section11660541593"></a>
**JS-UI框架子系統**，是OpenHarmony為開發者提供的一套開發OpenHarmony應用的JS-UI框架。 其組成如下所示：
**圖1** JS-UI框架子系統<a name="fig11520531310"></a>
！ []（figures/JS-UI框架子系統.png"JS-UI框架子系統"）
JS-UI框架子系統包括JS數據綁定框架（JS Data binding）、JS運行時（JS runtime）和JS框架（JS framework）。
- **JS Data binding**
JS數據綁定框架使用JavaScript語言提供一套基礎的數據綁定能力。
- **JS runtime**
JS運行時用以支持JS程式碼的解析和執行。
- **JS framework**
JS框架部分使用C++語言提供JS API和組件的框架機制。
##目錄<a name="section1464106163817"></a>
JS-UI框架子系統原始程式碼在/foundation/arkui/arkui\_ ace\_ engine\_ lite下，目錄結構如下圖所示：
```
/foundation/arkui/arkui_ ace_ engine_ lite
├——frameworks #框架程式碼目錄
│├——common #公共工具類目錄
│├——examples #示例代碼目錄
│├——include #標頭檔目錄
│├——module_ manager # JS模塊管理類目錄
│├——native_ engine # JS引擎適配層目錄
│├——packages #框架JS實現存放目錄
│├——src #原始程式碼存放目錄
│├——targets #各目標設備設定檔存放目錄
│└——tools #工具程式碼存放目錄
├——interfaces #對外介面存放目錄
│└——innerkits #對內部子系統暴露的標頭檔存放目錄
│└——builtin # JS-UI框架子系統對外暴露JS三方module API介面存放目錄
└——test #測試用例目錄
```
## 介面<a name="section1096322014288"></a>

API介紹請參攷[《OpenHarmony Device開發API參考》]（ https://device.harmonyos.com/cn/docs/develop/apiref/js-framework-file-0000000000611396 ）

## 使用<a name="section1529834174016"></a>

詳見：
[ https://gitee.com/openharmony/docs/blob/master/zh-cn/readme/JS-UI 框架子系統.md]（ https://gitee.com/openharmony/docs/blob/master/zh-cn/readme/JS-UI 框架子系統.md）

## 相關倉<a name="section11683135113011"></a>

[arkui\_ace\_engine\_lite]（ https://gitee.com/openharmony/arkui_ace_engine_lite ）
