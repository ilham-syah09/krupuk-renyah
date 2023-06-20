<div class="main-content">
    <section class="section">
        <div class="section-header">
            <h1><?= $title; ?></h1>
        </div>

        <div class="section-body">
            <div class="row">
                <div class="col-md-4">
                    <div class="card card-danger">
                        <div class="card-header">
                            <h4>Setting Suhu</h4>
                        </div>
                        <div class="card-body">
                            <form action="<?= base_url('setting/setSuhu'); ?>" method="post">
                                <input type="hidden" value="<?= $setting->id; ?>" name="id">
                                <div class="form-group">
                                    <input class="form-control" type="text" value="<?= $setting->setSuhu; ?>" name="setSuhu">
                                </div>
                                <button type="submit" class="btn btn-primary">save</button>
                            </form>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <!-- end main -->

    </section>
</div>