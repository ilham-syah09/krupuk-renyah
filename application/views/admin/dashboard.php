<div class="main-content">
    <section class="section">
        <div class="section-header">
            <h1><?= $title; ?></h1>
        </div>
        <div class="section-body">
            <div class="row">
                <div class="col-md-4">
                    <div class="card card-statistic-1">
                        <div class="card-icon bg-danger">
                            <i class="fas fa-thermometer-2 "></i>
                        </div>
                        <div class="card-wrap">
                            <div class="card-header">
                                <h4>Suhu Saat Ini</h4>
                            </div>
                            <div class="card-body">
                                <span id="suhu"></span>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="col-md-4">
                    <div class="card card-statistic-1">
                        <div class="card-icon bg-danger">
                            <i class="fas fa-bell"></i>
                        </div>
                        <div class="card-wrap">
                            <div class="card-header">
                                <h4>Status Kipas</h4>
                            </div>
                            <div class="card-body">
                                <span id="status"></span>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </section>
</div>

<script src="<?= base_url('assets/highcharts/highcharts.js'); ?>"></script>
<script src="<?= base_url('assets/highcharts/exporting.js'); ?>"></script>
<script src="<?= base_url('assets/highcharts/export-data.js'); ?>"></script>
<script src="<?= base_url('assets/highcharts/accessibility.js'); ?>"></script>
<script>
    function realtime() {
        $.ajax({
            url: "<?= base_url('admin/realtime'); ?>",
            dataType: "json",
            success: function(response) {
                $('#suhu').text(response.suhu);
                $('#status').text(response.status);

                setTimeout(realtime, 2000);
            }

        });
    }

    realtime();
</script>