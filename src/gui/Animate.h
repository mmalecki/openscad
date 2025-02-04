#pragma once

#include "qtgettext.h"
#include "ui_Animate.h"
#include <QIcon>
#include "input/InputDriverEvent.h"

class MainWindow;

class Animate : public QWidget, public Ui::AnimateWidget
{
  Q_OBJECT

public:
  Animate(QWidget *parent = nullptr);
  Animate(const Animate& source) = delete;
  Animate(Animate&& source) = delete;
  Animate& operator=(const Animate& source) = delete;
  Animate& operator=(Animate&& source) = delete;

  void initGUI();
  bool dumpPictures();
  int nextFrame();

  QTimer *animate_timer;

  void setMainWindow(MainWindow *mainWindow);

  const QList<QAction *>& actions();
  double getAnim_tval();
  QSize minimumSizeHint() const override;

public slots:
  void animateUpdate();
  void cameraChanged();
  void editorContentChanged();
  void onActionEvent(InputEventAction *event);
  void pauseAnimation();

protected:
  void resizeEvent(QResizeEvent *event) override;


private:
  MainWindow *mainWindow;

  void updatePauseButtonIcon();

  double anim_tval;
  bool anim_dumping;
  int anim_dump_start_step;
  int anim_step;
  int anim_numsteps;

  bool isLightTheme();
  
  bool fps_ok;
  bool t_ok;
  bool steps_ok;

  QList<QAction *> action_list;

signals:

private slots:
  void updatedAnimTval();
  void updatedAnimFpsAndAnimSteps();
  void updatedAnimDump(bool checked);
  void updateTVal();
  void on_pauseButton_pressed();
};
