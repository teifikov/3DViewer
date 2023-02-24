#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  Timer = new QTimer(this);
  settings = new QSettings("Setting", "3dviewer", this);
  this->setWindowTitle("3D Viewer");
  ui->zoom_bar->setMinimum(-100);
  ui->zoom_bar->setMaximum(100);
  ui->up_down_bar->setMinimum(-100);
  ui->up_down_bar->setMaximum(100);
  ui->left_right_bar->setMinimum(-100);
  ui->left_right_bar->setMaximum(100);
  ui->front_back_bar->setMaximum(100);
  ui->front_back_bar->setMinimum(-100);
  ui->rotate_bar_front_back->setMinimum(-100);
  ui->rotate_bar_front_back->setMaximum(100);
  ui->rotate_bar_right_left->setMinimum(-100);
  ui->rotate_bar_right_left->setMaximum(100);
  ui->rotate_bar_up_down->setMaximum(100);
  ui->rotate_bar_up_down->setMinimum(-100);
  ui->wigth_line->setMinimum(0);
  ui->wigth_line->setMaximum(50);
  ui->size_vertice->setMinimum(0);
  ui->size_vertice->setMaximum(50);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_open_file_clicked() {
  filename = QFileDialog::getOpenFileName(this, tr("Open file"),
                                          "../../../../Exzample_obj",
                                          tr("OBJ Files (*.obj)"));
  if (filename.isEmpty()) {
    QMessageBox::warning(this, "ERROR", "OOOOOOPSSS🙀");
    return;
  }

  std::string str = filename.toStdString();
  char *cstr = new char[str.length() + 1];
  strcpy(cstr, str.c_str());
  char name_forlabel[20];
  file_name(cstr, name_forlabel);
  ui->label_path_to_file->setText(name_forlabel);
  DataStr = parser(cstr);

  ui->openGLWidget->vertex_len = DataStr.countVertexes;
  ui->openGLWidget->facets_len = DataStr.countFacets * 2;
  ui->openGLWidget->vertex_arr = DataStr.dataVertexes;
  ui->openGLWidget->facets_arr = DataStr.dataFacets;
  ui->openGLWidget->minVerX = DataStr.minVertexesX;
  ui->openGLWidget->maxVerX = DataStr.maxVertexesX;
  ui->openGLWidget->minVerY = DataStr.minVertexesY;
  ui->openGLWidget->maxVerY = DataStr.maxVertexesY;
  ui->openGLWidget->minVerZ = DataStr.minVertexesZ;
  ui->openGLWidget->maxVerZ = DataStr.maxVertexesZ;

  V_nam = QString::number(DataStr.countVertexes);
  F_nam = QString::number(DataStr.countFacets * 2);

  ui->label_vert_num->setText(V_nam);
  ui->label_vert_num_2->setText(F_nam);
}

void MainWindow::file_name(char *str, char *result) {
  for (int i = strlen(str) - 1; i >= 0; i--) {
    if (str[i] == '/') {
      for (int j = i + 1, a = 0; j <= strlen(str) - 1; j++, a++) {
        result[a] = str[j];
      }
      break;
    }
  }
}

// сдвиги
void MainWindow::on_up_down_bar_valueChanged(int value) {
  ui->up_down_int->setText(QString::number(value));
}

void MainWindow::on_up_down_int_textChanged(const QString &arg1) {
  int c = arg1.toInt();
  ui->up_down_bar->setValue(c);
  double i = arg1.toDouble();
  move_arr[1] = i - move_arr_buff[1];
  moving_form();
  move_arr_buff[1] = i;
}

void MainWindow::on_reset_up_down_clicked() {
  ui->up_down_bar->setValue(0);
  res_move[1] = 1;
  reset_move_by_axis(&DataStr, res_move);
}

void MainWindow::on_left_right_bar_valueChanged(int value) {
  ui->left_right_int->setText(QString::number(value));
}

void MainWindow::on_left_right_int_textChanged(const QString &arg1) {
  int d = arg1.toInt();
  ui->left_right_bar->setValue(d);
  double i = arg1.toDouble();
  move_arr[0] = i - move_arr_buff[0];
  moving_form();
  move_arr_buff[0] = i;
}

void MainWindow::on_reset_left_r_clicked() {
  ui->left_right_bar->setValue(0);
  res_move[0] = 1;
  reset_move_by_axis(&DataStr, res_move);
}

void MainWindow::on_front_back_bar_valueChanged(int value) {
  ui->back_front_int->setText(QString::number(value));
}

void MainWindow::on_back_front_int_textChanged(const QString &arg1) {
  int d = arg1.toInt();
  ui->front_back_bar->setValue(d);
  double i = arg1.toDouble();
  move_arr[2] = i - move_arr_buff[2];
  moving_form();
  move_arr_buff[2] = i;
}

void MainWindow::on_reset_front_back_clicked() {
  ui->front_back_bar->setValue(0);
  res_move[2] = 1;
  reset_move_by_axis(&DataStr, res_move);
}

void MainWindow::moving_form() {
  move_arr[0] = move_arr[0] / 100;
  move_arr[1] = move_arr[1] / 100;
  move_arr[2] = move_arr[2] / 100;

  move_form(&DataStr, move_arr);

  ui->openGLWidget->update();
}

// rotate bar
void MainWindow::on_rotate_bar_right_left_valueChanged(int value) {
  ui->rotate_right_left_int->setText(QString::number(value));
}

void MainWindow::on_rotate_right_left_int_textChanged(const QString &arg1) {
  int d = arg1.toInt();
  ui->rotate_bar_right_left->setValue(d);
  double i = arg1.toDouble();
  rotate_arr[0] = i - rotate_arr_buff[0];
  rotating_form();
  rotate_arr_buff[0] = i;
}

void MainWindow::on_reset_rotate_right_left_clicked() {
  ui->rotate_bar_right_left->setValue(0);
}

void MainWindow::on_rotate_bar_up_down_valueChanged(int value) {
  ui->rotate_up_down_int->setText(QString::number(value));
}

void MainWindow::on_rotate_up_down_int_textChanged(const QString &arg1) {
  int d = arg1.toInt();
  ui->rotate_bar_up_down->setValue(d);
  double i = arg1.toDouble();
  rotate_arr[1] = i - rotate_arr_buff[1];
  rotating_form();
  rotate_arr_buff[1] = i;
}

void MainWindow::on_reset_rotate_2_clicked() {
  ui->rotate_bar_up_down->setValue(0);
}

void MainWindow::on_rotate_bar_front_back_valueChanged(int value) {
  ui->rotate_back_front_int->setText(QString::number(value));
}

void MainWindow::on_rotate_back_front_int_textChanged(const QString &arg1) {
  int d = arg1.toInt();
  ui->rotate_bar_front_back->setValue(d);
  rotate_arr[2] = d - rotate_arr_buff[2];
  rotating_form();
  rotate_arr_buff[2] = d;
}

void MainWindow::on_reset_rotate_3_clicked() {
  ui->rotate_bar_front_back->setValue(0);
}

void MainWindow::rotating_form() {
  rotate_arr[0] = rotate_arr[0] / 10;
  rotate_arr[1] = rotate_arr[1] / 10;
  rotate_arr[2] = rotate_arr[2] / 10;

  rotate_form(&DataStr, rotate_arr);

  ui->openGLWidget->update();
}

void MainWindow::on_zoom_bar_valueChanged(int value) {
  ui->zoom_int->setText(QString::number(value));
}

void MainWindow::on_zoom_int_textChanged(const QString &arg1) {
  int a = arg1.toInt();
  ui->zoom_bar->setValue(a);
  double z = arg1.toDouble();
  zoom_form(z);
  zoom_buff = z;
}

void MainWindow::on_resetzoom_clicked() {
  ui->zoom_bar->setValue(0);
  reset_zoom(&DataStr, 0.9);
}

void MainWindow::zoom_form(double c) {
  if (c > zoom_buff) {
    resize_form_less(&DataStr, zoom, cur_zoom_l, cur_zoom_m);
  } else {
    resize_form_more(&DataStr, zoom, cur_zoom_m, cur_zoom_l);
  }
  ui->openGLWidget->update();
}

void MainWindow::on_background_clicked() {
  QColor ColorValue =
      QColorDialog::getColor(Qt::gray, this, tr("Select color"));
  qDebug() << ColorValue;
  QPalette p = ui->openGLWidget->palette();
  //    QPalette p = ui->openGLWidget->colorCount();
  //    QPalette p = ui->openGLWidget->colorCount();
  p.setColor(QPalette::Base, ColorValue);
  ui->openGLWidget->setAutoFillBackground(true);
  ui->openGLWidget->setPalette(p);
  ui->openGLWidget->show();
}

void MainWindow::on_wigth_line_valueChanged(int value) {
  ui->wigthline_int->setText(QString::number(value));
  ui->openGLWidget->Width_Line = value;
  ui->openGLWidget->update();
}

void MainWindow::on_reset_widthline_clicked() { ui->wigth_line->setValue(0); }

void MainWindow::on_wigthline_int_textChanged(const QString &arg1) {
  int e = arg1.toInt();
  ui->wigth_line->setValue(e);
}

void MainWindow::on_comboBox_lines_currentIndexChanged(int index) {
  ui->openGLWidget->LineType = index;
  ui->openGLWidget->update();
}

void MainWindow::on_Central_radioButton_toggled(bool checked) {
  ui->openGLWidget->central = checked;
  ui->openGLWidget->update();
}

void MainWindow::on_Parallel_radioButton_toggled(bool checked) {
  ui->openGLWidget->parallel = checked;
  ui->openGLWidget->update();
}

void MainWindow::on_comboBox_vertice_currentIndexChanged(int index) {
  ui->openGLWidget->VertType = index;
  ui->openGLWidget->update();
}

void MainWindow::on_size_vertice_valueChanged(int value) {
  ui->sizevertice_int->setText(QString::number(value));
  ui->openGLWidget->size_vertice = value;
  ui->openGLWidget->update();
}

void MainWindow::on_sizevertice_int_textChanged(const QString &arg1) {
  int e = arg1.toInt();
  ui->size_vertice->setValue(e);
}

void MainWindow::on_reset_sizevertice_clicked() {
  ui->size_vertice->setValue(0);
}

void MainWindow::on_background_R_bar_valueChanged(int value) {
  ui->openGLWidget->BackR = value;
  ui->openGLWidget->update();
}

void MainWindow::on_background_G_bar_valueChanged(int value) {
  ui->openGLWidget->BackG = value;
  ui->openGLWidget->update();
}

void MainWindow::on_background_B_bar_valueChanged(int value) {
  ui->openGLWidget->BackB = value;
  ui->openGLWidget->update();
}

void MainWindow::on_line_R_bar_valueChanged(int value) {
  ui->openGLWidget->LineR = value;
  ui->openGLWidget->update();
}

void MainWindow::on_line_G_bar_valueChanged(int value) {
  ui->openGLWidget->LineG = value;
  ui->openGLWidget->update();
}

void MainWindow::on_line_B_bar_valueChanged(int value) {
  ui->openGLWidget->LineB = value;
  ui->openGLWidget->update();
}

void MainWindow::on_point_R_bar_valueChanged(int value) {
  ui->openGLWidget->VertR = value;
  ui->openGLWidget->update();
}

void MainWindow::on_point_G_bar_valueChanged(int value) {
  ui->openGLWidget->VertG = value;
  ui->openGLWidget->update();
}

void MainWindow::on_point_B_bar_valueChanged(int value) {
  ui->openGLWidget->VertB = value;
  ui->openGLWidget->update();
}

void MainWindow::on_JPEG_clicked() {
  JPGfile = QFileDialog::getSaveFileName(this, tr("Screenshot JPG"), Path,
                                         tr("JPG files (*.jpg)"));
  QImage Screenshot = ui->openGLWidget->grabFramebuffer();
  Screenshot.save(JPGfile, nullptr, 80);
}

void MainWindow::on_BMP_clicked() {
  BMPfile = QFileDialog::getSaveFileName(this, tr("Screenshot BMP"), Path,
                                         tr("BMP files (*.bmp)"));
  QImage Screenshot = ui->openGLWidget->grabFramebuffer();
  Screenshot.save(BMPfile, nullptr, 80);
}

void MainWindow::on_GIF_clicked() {
  connect(Timer, SIGNAL(timeout()), this, SLOT(AddFrameInGifTime()));

  Timer->start(100);  // 100 милисекунд => 50 кадров за 5 сек

  ui->GIF->setDisabled(true);  // отключаем кнопку на время записи
}

void MainWindow::AddFrameInGifTime() {
  if (FramesCount <= 50) {
    gif.push_back(ui->openGLWidget->grabFramebuffer());

    FramesCount++;

  } else {
    Timer->stop();

    GIFfile = QFileDialog::getSaveFileName(this, tr("Save gif"), Path,

                                           tr("GIF files (*.gif)"));

    if (!GIFfile.isNull()) {
      QGifImage gif_file(

          QSize(ui->openGLWidget->width() * 2, ui->openGLWidget->height() * 2));

      gif_file.setDefaultDelay(100);

      for (QVector<QImage>::Iterator frames = gif.begin(); frames != gif.end();

           frames++) {
        gif_file.addFrame(*frames);
      }

      gif_file.save(GIFfile);
    }

    gif.clear();

    FramesCount = 0;

    ui->GIF->setEnabled(true);
  }
}

void MainWindow::on_Save_settings_clicked() {
  settings->setValue("BackR", ui->openGLWidget->BackR);
  settings->setValue("BackG", ui->openGLWidget->BackG);
  settings->setValue("BackB", ui->openGLWidget->BackB);

  settings->setValue("LineR", ui->openGLWidget->LineR);
  settings->setValue("LineG", ui->openGLWidget->LineG);
  settings->setValue("LineB", ui->openGLWidget->LineB);

  settings->setValue("VertR", ui->openGLWidget->VertR);
  settings->setValue("VertG", ui->openGLWidget->VertG);
  settings->setValue("VertB", ui->openGLWidget->VertB);

  settings->setValue("LineWidth", ui->openGLWidget->LineWidth);

  settings->setValue("LineTypeIndex", ui->openGLWidget->LineTypeIndex);
  settings->setValue("VertTypeIndex", ui->openGLWidget->VertTypeIndex);

  settings->setValue("VertScale", ui->openGLWidget->VertScale);
  settings->setValue("projection_type", ui->openGLWidget->projection_type);
}

void MainWindow::on_Reset_settings_clicked() {
  ui->openGLWidget->BackR = 0;
  ui->openGLWidget->BackG = 0;
  ui->openGLWidget->BackB = 0;

  ui->openGLWidget->LineR = 100;
  ui->openGLWidget->LineG = 100;
  ui->openGLWidget->LineB = 100;

  ui->openGLWidget->VertR = 100;
  ui->openGLWidget->VertG = 100;
  ui->openGLWidget->VertB = 100;

  ui->openGLWidget->LineWidth = 0;

  ui->openGLWidget->LineTypeIndex = 0;
  ui->openGLWidget->VertTypeIndex = 0;

  ui->openGLWidget->VertScale = 0;
  ui->openGLWidget->projection_type = 0;

  ui->openGLWidget->update();
}

void MainWindow::on_load_clicked() {
  ui->openGLWidget->BackR = settings->value("BackR").toDouble();
  ui->openGLWidget->BackG = settings->value("BackG").toDouble();
  ui->openGLWidget->BackB = settings->value("BackB").toDouble();
  ui->openGLWidget->LineR = settings->value("LineR").toDouble();
  ui->openGLWidget->LineG = settings->value("LineG").toDouble();
  ui->openGLWidget->LineB = settings->value("LineB").toDouble();
  ui->openGLWidget->VertR = settings->value("VertR").toDouble();
  ui->openGLWidget->VertG = settings->value("VertG").toDouble();
  ui->openGLWidget->VertB = settings->value("VertB").toDouble();
  ui->openGLWidget->LineWidth = settings->value("LineWidth").toDouble();
  ui->openGLWidget->LineTypeIndex = settings->value("LineTypeIndex").toInt();
  ui->openGLWidget->VertTypeIndex = settings->value("VertTypeIndex").toInt();
  ui->openGLWidget->VertScale = settings->value("VertScale").toDouble();
  ui->openGLWidget->projection_type =
      settings->value("projection_type").toInt();
}
